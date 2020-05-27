#include <stdlib.h>
#include <stdio.h>
#include "extmem.h"

typedef struct data_blk{
	int X[7];
    int Y[7];
    int addr;
}data_blk;

int menu(){
    int choice;
	printf("��ѡ������һ�\n");
    printf("1.�������������Ĺ�ϵѡ��(R.A=30��Ԫ��)\n");
	printf("2.���׶ζ�·�鲢�����㷨��TPMMS��,����ϵR��S�ֱ�����\n");
	printf("3.���������Ĺ�ϵѡ�񣺽��������ļ���ѡ��R.A=30��Ԫ��\n");
	printf("4.ʵ�ֹ�ϵͶӰ�㷨���Թ�ϵR�ϵ�A���Խ���ͶӰ��ȥ��\n");
	printf("5.������������Ӳ������Թ�ϵR��S����R.A����S.C\n");
	printf("6.��������ļ��ϵĽ��㷨\n");
	printf("7.��������ļ��ϵĲ��㷨\n");
	printf("8.��������ļ��ϵĲ��㷨R-S\n");
	printf("0.�˳�\n");
	printf("������ѡ�");
	scanf("%d",&choice);
	return choice;
}


void init_data_blk(data_blk *data){
	int i;
	data -> addr = -1;
	for (i=0; i<7; i++){
		data -> X[i] = -1;
		data -> Y[i] = -1;
	}
}


// ������ÿ��blk����Ϣ��7��Ԫ���1����ַ��
void read_data_blk(unsigned char *blk, data_blk *data){
	int i=0;
	char str[5];
	for (i = 0; i < 7; i++) //һ��blk��7��Ԫ���һ����ַ
    {

        for (int k = 0; k < 4; k++)
        {
            str[k] = *(blk + i*8 + k);
        }
        data->X[i] = atoi(str);
        for (int k = 0; k < 4; k++)
        {
            str[k] = *(blk + i*8 + 4 + k);
        }
        data->Y[i] = atoi(str);
    }
    for (int k = 0; k < 4; k++)
    {
        str[k] = *(blk + i*8 + k);
    }
    data->addr = atoi(str);
}


//����д�ض�result����Ϣ
void write_data_blk(unsigned char *blk, data_blk res){
	int i=0;
	char str[5];
	for (i = 0; i < 7; i++) //һ��blk��7��Ԫ���һ����ַ
    {
		itoa(res.X[i],str,10);
        for (int k = 0; k < 4; k++)
        {
            *(blk + i*8 + k) = str[k];
        }
        itoa(res.Y[i],str,10);
        for (int k = 0; k < 4; k++)
        {
            *(blk + i*8 + 4 + k) = str[k];
        }
    }
	itoa(res.addr,str,10);
    for (int k = 0; k < 4; k++)
    {
        *(blk + i*8 + k) = str[k];
	}
}


int func1(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("��������������ѡ���㷨 R.A=30\n");
    printf("------------------------------------------------------------\n");
	unsigned char *blk;
    unsigned char *result;
	result = getNewBlockInBuffer(buf);	//������������Ԫ��ȫ����¼��result����
	data_blk data;	//�ݴ�����blk����Ϣ
	init_data_blk(&data);
	data_blk res;	//res�ݴ�Ҫд��result����Ϣ
	init_data_blk(&res);
	int count = 0;	//��¼R.A=30�ж��ٸ�Ԫ��
	int cur_blk = 1;
	for(cur_blk = 1; cur_blk<=16; cur_blk++){
		if ((blk = readBlockFromDisk(cur_blk, buf)) == NULL)
		{
			perror("Reading Block Failed!\n");
			return -1;
		}
		printf("�������ݿ�%d\n", cur_blk);
		read_data_blk(blk, &data);
		int i = 0;
		for(i=0; i<8; i++){
			if(data.X[i]==30){
				printf("(X=%d, Y=%d)\n",data.X[i],data.Y[i]);
				res.X[count] = data.X[i];
				res.Y[count] = data.Y[i];
				count++;
			}
		}
		freeBlockInBuffer(blk, buf);
	}
	res.addr = 0;
	write_data_blk(result, res);
	if (writeBlockToDisk(result, 1111, buf) != 0)
    {
        perror("Writing Block Failed!\n");
        return -1;
    }
	printf("ע�����д����̣�1111\n\n");
	printf("����ѡ��������Ԫ��һ��%d����\n\n", count);
	printf("IO��дһ��%ld�Ρ�\n\n", buf->numIO);
	freeBlockInBuffer(result, buf);
	return 0;
}


int tpmms(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("���׶ζ�·�鲢�����㷨��TPMMS��,����ϵR��S�ֱ�����\n");
    printf("------------------------------------------------------------\n");
	//����ϵR��4*4���Ӽ�������������101.blk-116.blk
	int i = 1;	//������4��
	int j = 0;	//ÿ����������4���飬ÿ������7��Ԫ��
	int k;	//ð����������Ҫ��
	for (i=1; i<=4; i++){
        data_blk data[4];	//�ݴ�����blk����Ϣ
        unsigned char *blk[4];
		for(j=0; j<=3; j++){
            init_data_blk(&data[j]);
		}

		for(j=0; j<=3; j++){
			if ((blk[j] = readBlockFromDisk((i-1)*4+j+1, buf)) == NULL)
			{
				perror("Reading Block Failed!\n");
				return -1;
			}
			read_data_blk(blk[j], &data[j]);	//��ȡ��Ϣ����
		}
		//ð������
		for (k=0; k<27; k++){
			for (j=0; j<27-k; j++){
				if(data[j/7].X[j%7] > data[(j+1)/7].X[(j+1)%7]){
					int tempx, tempy;
					tempx = data[j/7].X[j%7];
					tempy = data[j/7].Y[j%7];
					data[j/7].X[j%7] = data[(j+1)/7].X[(j+1)%7];
					data[j/7].Y[j%7] = data[(j+1)/7].Y[(j+1)%7];
					data[(j+1)/7].X[(j+1)%7] = tempx;
					data[(j+1)/7].Y[(j+1)%7] = tempy;
				}
			}
		}

		//��������101.blk-116.blk
		for(j=0; j<=3; j++){
			data[j].addr = 102+(i-1)*4+j;
			if(i==4&&j==3)	data[j].addr = 0;

			/*
			for(int m=0; m<7; m++){
				printf("%d %d\n", data[j].X[m], data[j].Y[m]);
			}
			printf("%d\n", data[j].addr);
			*/

			write_data_blk(blk[j], data[j]);
			if (writeBlockToDisk(blk[j], 101+(i-1)*4+j, buf) != 0)
			{
				perror("Writing Block Failed!\n");
				return -1;
			}
			freeBlockInBuffer(blk[j], buf);
		}
		// printf("\n");
	}

	//ÿ���Ӽ����������ٽ��й鲢���鲢��������301.blk-316.blk
	unsigned char *blk[4];	//��¼4������Ŀ�
	for (i=0; i<4; i++)
		blk[i] = readBlockFromDisk(i*4+101, buf);
    data_blk ready[4];	//�ݴ�����blk����Ϣ

	int group[4];	//��¼4�������������˼���
	for (i=0; i<4; i++)
		group[i]=1;

	unsigned char *compare, *output;
	compare = getNewBlockInBuffer(buf); //�����бȽϿ�
	data_blk cmp;	//�ݴ�ȽϿ����Ϣ
	init_data_blk(&cmp);

	int pointer[4]; //��¼���뻺��Ŀ鵽���ĸ�Ԫ��
	for (i=0; i<4; i++)
		pointer[i]=0;

	output = getNewBlockInBuffer(buf); //�����������
	data_blk out;	//�ݴ���������Ϣ
	init_data_blk(&out);
	int outnum = 0;	//��¼������Ѿ���¼�˶��ٸ�����
	int outaddr = 302;

	while(group[0]<=4||group[1]<=4||group[2]<=4||group[3]<=4){
		//һ��������ˣ���Ҫ����
		for (i=0; i<4; i++){
			if(pointer[i]==7){
				if (group[i]<4){
					freeBlockInBuffer(blk[i], buf);
					blk[i] = readBlockFromDisk(i*4+group[i]+101, buf);
					pointer[i] = 0;
				}
				group[i]++;
			}
		}

		int flag[4];	//��¼�����Ƿ��Ѿ������ˣ�1�Ƕ����ˣ�0δ���꣩
		for (i=0; i<4; i++){
			if(group[i]<=4)
				flag[i]=0;
			else
				flag[i]=1;
		}

		init_data_blk(&cmp);
		int min = 1001;
		int index = -1;
		for(j=0; j<=3; j++){
			if(!flag[j]){
				init_data_blk(&ready[j]);
				read_data_blk(blk[j], &ready[j]);
				int pos = pointer[j];
				cmp.X[j] = ready[j].X[pos];
				cmp.Y[j] = ready[j].Y[pos];
				if(cmp.X[j]<min){
					index = j;
					min = cmp.X[j];
				}
			}
		}

		write_data_blk(compare, cmp);
		pointer[index] ++;
		out.X[outnum] = cmp.X[index];
		out.Y[outnum] = cmp.Y[index];
		outnum++;
		//������дд���������
		if(outnum==7){
			if(outaddr==317)	outaddr=0;
			out.addr = outaddr;
			/*
			for(int m=0; m<7; m++){
				printf("%d %d\n", out.X[m], out.Y[m]);
			}
			printf("%d\n\n", out.addr);
			*/

			write_data_blk(output, out);
			init_data_blk(&out);
			outnum = 0;
			if(outaddr==0)	outaddr=317;
			writeBlockToDisk(output, outaddr-1, buf);
			outaddr++;
		}
	}
	freeBlockInBuffer(output, buf);
	freeBlockInBuffer(compare, buf);
	for(i=0; i<4; i++){
		freeBlockInBuffer(blk[i], buf);
	}


	//����ϵS��4*8���Ӽ�������������117.blk-148.blk
	for (i=1; i<=4; i++){
		data_blk data[8];	//�ݴ�����blk����Ϣ
		unsigned char *blk[8];
		for(j=0; j<=7; j++){
            init_data_blk(&data[j]);
		}

		for(j=0; j<=7; j++){
			if ((blk[j] = readBlockFromDisk((i-1)*8+j+17, buf)) == NULL)
			{
				perror("Reading Block Failed!\n");
				return -1;
			}
			read_data_blk(blk[j], &data[j]);	//��ȡ��Ϣ����
		}

		//ð������
		for (k=0; k<55; k++){
			for (j=0; j<55-k; j++){
				if(data[j/7].X[j%7] > data[(j+1)/7].X[(j+1)%7]){
					int tempx, tempy;
					tempx = data[j/7].X[j%7];
					tempy = data[j/7].Y[j%7];
					data[j/7].X[j%7] = data[(j+1)/7].X[(j+1)%7];
					data[j/7].Y[j%7] = data[(j+1)/7].Y[(j+1)%7];
					data[(j+1)/7].X[(j+1)%7] = tempx;
					data[(j+1)/7].Y[(j+1)%7] = tempy;
				}
			}
		}

		//��������117.blk-148.blk
		for(j=0; j<=7; j++){
			data[j].addr = 118+(i-1)*8+j;
			if(i==4&&j==7)	data[j].addr = 0;

            /*
			for(int m=0; m<7; m++){
				printf("%d %d\n", data[j].X[m], data[j].Y[m]);
			}
			printf("%d\n", data[j].addr);
            */

			write_data_blk(blk[j], data[j]);
			if (writeBlockToDisk(blk[j], 117+(i-1)*8+j, buf) != 0)
			{
				perror("Writing Block Failed!\n");
				return -1;
			}
			freeBlockInBuffer(blk[j], buf);
		}
		//printf("\n");
	}

	//ÿ���Ӽ����������ٽ��й鲢���鲢��������317.blk-348.blk
	//unsigned char *blk[4];	//��¼4������Ŀ�
	for (i=0; i<4; i++)
		blk[i] = readBlockFromDisk(i*8+117, buf);
    //data_blk ready[4];	//�ݴ�����blk����Ϣ

	//int group[4];	//��¼4�������������˼���
	for (i=0; i<4; i++)
		group[i]=1;

	//unsigned char *compare, *output;
	compare = getNewBlockInBuffer(buf); //�����бȽϿ�
	//data_blk cmp;	//�ݴ�ȽϿ����Ϣ
	init_data_blk(&cmp);

	//int pointer[4]; //��¼���뻺��Ŀ鵽���ĸ�Ԫ��
	for (i=0; i<4; i++)
		pointer[i]=0;

	output = getNewBlockInBuffer(buf); //�����������
	//data_blk out;	//�ݴ���������Ϣ
	init_data_blk(&out);
	outnum = 0;	//��¼������Ѿ���¼�˶��ٸ�����
	outaddr = 318;

	while(group[0]<=8||group[1]<=8||group[2]<=8||group[3]<=8){
		//һ��������ˣ���Ҫ����
		for (i=0; i<4; i++){
			if(pointer[i]==7){
				if (group[i]<8){
					freeBlockInBuffer(blk[i], buf);
					blk[i] = readBlockFromDisk(i*8+group[i]+117, buf);
					pointer[i] = 0;
				}
				group[i]++;
			}
		}

		int flag[4];	//��¼�����Ƿ��Ѿ������ˣ�1�Ƕ����ˣ�0δ���꣩
		for (i=0; i<4; i++){
			if(group[i]<=8)
				flag[i]=0;
			else
				flag[i]=1;
		}

		init_data_blk(&cmp);
		int min = 1001;
		int index = -1;
		for(j=0; j<=3; j++){
			if(!flag[j]){
				init_data_blk(&ready[j]);
				read_data_blk(blk[j], &ready[j]);
				int pos = pointer[j];
				cmp.X[j] = ready[j].X[pos];
				cmp.Y[j] = ready[j].Y[pos];
				if(cmp.X[j]<min){
					index = j;
					min = cmp.X[j];
				}
			}
		}

		write_data_blk(compare, cmp);
		pointer[index] ++;
		out.X[outnum] = cmp.X[index];
		out.Y[outnum] = cmp.Y[index];
		outnum++;
		//������дд���������
		if(outnum==7){
			if(outaddr==349)	outaddr=0;
			out.addr = outaddr;

			/*
			for(int m=0; m<7; m++){
				printf("%d %d\n", out.X[m], out.Y[m]);
			}
			printf("%d\n\n", out.addr);
			*/

			write_data_blk(output, out);
			init_data_blk(&out);
			outnum = 0;
			if(outaddr==0)	outaddr=349;
			writeBlockToDisk(output, outaddr-1, buf);
			outaddr++;
		}
	}
	freeBlockInBuffer(output, buf);
	freeBlockInBuffer(compare, buf);
	for(i=0; i<4; i++){
		freeBlockInBuffer(blk[i], buf);
	}
	printf("��ϵR�����������ļ�301.blk��316.blk\n");
	printf("��ϵS�����������ļ�317.blk��348.blk\n\n");
	return 0;
}

int setindex(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("���������Ĺ�ϵѡ�񣺽��������ļ���ѡ��R.A=30��Ԫ��\n");
    printf("------------------------------------------------------------\n");
	//��������
	int i, j;
	int indexnum[41];
	for (i=0; i<41; i++){
		indexnum[i] = 318;
	}

	data_blk index;
	for (i=0; i<6; i++){
		init_data_blk(&index);
	}
	unsigned char *blk, *save;
	save = getNewBlockInBuffer(buf);
	for (i=301; i<317; i++){
		blk = readBlockFromDisk(i, buf);
		data_blk data;
		init_data_blk(&data);
		read_data_blk(blk, &data);
		for (j=0; j<7; j++){
			if (i<indexnum[data.X[j]]){
				indexnum[data.X[j]] = i;
			}
		}
		freeBlockInBuffer(blk, buf);
	}
	int addr = 349;
	int count = 0;
	for (i=1; i<41; i++){
		if(indexnum[i]!=318){
			index.X[count] = i;
			index.Y[count] = indexnum[i];
			count++;
			if(count==7){
				index.addr = addr+1;
				/*
				for(int m=0; m<7; m++){
					printf("%d %d\n", index.X[m], index.Y[m]);
				}
				printf("%d\n\n", index.addr);
				*/
				write_data_blk(save, index);
				writeBlockToDisk(save, addr, buf);
				init_data_blk(&index);
				addr++;
				count = 0;
			}
		}
	}
	if(count>0){
		index.addr = 0;
		/*
		for(int m=0; m<7; m++){
			printf("%d %d\n", index.X[m], index.Y[m]);
		}
		printf("%d\n\n", index.addr);
		*/
		write_data_blk(save, index);
		writeBlockToDisk(save, addr, buf);
	}
	freeBlockInBuffer(save, buf);
    return 0;
}


int func3(Buffer *buf){
	int i, j, pos[2];
	int flag = 0;
	unsigned char *blk, *output;
	data_blk data;

	buf->numIO = 0;

	for (i=349; i<=354; i++){
		blk = readBlockFromDisk(i, buf);
		printf("����������%d\n", i);
		init_data_blk(&data);
		read_data_blk(blk, &data);
		for (j=0; j<8; j++){
			if(data.X[j]==30){
				pos[0] = data.Y[j];
			}
			if(data.X[j]==31){
				pos[1] = data.Y[j];
				flag=1;
			}
		}
		if(flag)
			break;
		else
			printf("û������������Ԫ�顣\n");
		freeBlockInBuffer(blk, buf);
	}

	output = getNewBlockInBuffer(buf);
	data_blk out;
	init_data_blk(&out);
	int count = 0;
	for(i=0; i<2; i++){
		blk = readBlockFromDisk(pos[i], buf);
		printf("�������ݿ�%d\n", pos[i]);
		read_data_blk(blk, &data);
		for (j=0; j<8; j++){
			if(data.X[j]==30){
				out.X[count] = data.X[j];
				out.Y[count] = data.Y[j];
				count++;
				printf("(X=%d, Y=%d)\n", data.X[j], data.Y[j]);
			}
		}
		freeBlockInBuffer(blk, buf);
	}
	out.addr = 0;
	write_data_blk(output, out);
	writeBlockToDisk(output, 3333, buf);
	printf("ע�����д����̣�3333\n\n");
	freeBlockInBuffer(output, buf);
	printf("����ѡ��������Ԫ��һ��%d����\n\n", count);
	printf("IO��дһ��%ld�Ρ�\n\n", buf->numIO);

    return 0;
}


int func4(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("ʵ�ֹ�ϵͶӰ�㷨���Թ�ϵR�ϵ�A���Խ���ͶӰ��ȥ��\n");
    printf("------------------------------------------------------------\n");
	unsigned char *blk, *output;
	int pre = 0;
	int i,j;
	output = getNewBlockInBuffer(buf);
	data_blk out;
	init_data_blk(&out);
	int count = 0;
	int addr = 401;
	for (i=301; i<317; i++){
		blk = readBlockFromDisk(i, buf);
		printf("�������ݿ�%d\n", i);
		data_blk data;
		init_data_blk(&data);
		read_data_blk(blk, &data);
		for (j=0; j<7; j++){
			if (data.X[j]!=pre){
				printf("(X=%d)\n", data.X[j]);
				out.X[count] = data.X[j];
				count++;
				pre = data.X[j];
				if(count==7){
					out.addr = addr+1;
					write_data_blk(output, out);
					writeBlockToDisk(output, addr, buf);
					printf("ע�����д����̣�%d\n", addr);
					init_data_blk(&out);
					addr++;
					count = 0;
				}
			}
		}
		freeBlockInBuffer(blk, buf);
	}
	if(count>0){
		out.addr = 0;
		write_data_blk(output, out);
		writeBlockToDisk(output, addr, buf);
		printf("ע�����д����̣�%d\n", addr);
	}
	printf("\n");
	freeBlockInBuffer(output, buf);
	return 0;
}


int func5(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("������������Ӳ������Թ�ϵR��S����R.A����S.C\n");
    printf("------------------------------------------------------------\n");
	unsigned char *blk_r, *compare;
	unsigned char *output[2];
	unsigned char *blk_s[4];
	int i, j, k;
	int group[4]; //Sÿ���Ѿ����˶��ٿ�
	int flag[4];	//���������Ϊ1������û����Ϊ0
	int pointer[4];	//Ŀǰ���ĸ�Ԫ��
	/*for(i=0; i<4; i++){
		flag[i] = 0;
		pointer[i] = 0;
	}*/
	data_blk data_s[4];
	/*for(i=0; i<4; i++){
		blk_s[i] = readBlockFromDisk(117+i*8, buf);
		group[i] = 1;
	}*/
	compare = getNewBlockInBuffer(buf);
	output[0] = getNewBlockInBuffer(buf);
	output[1] = getNewBlockInBuffer(buf);
	data_blk data_r, cmp;
	data_blk out[2];
	int outnum = 0;	//���������������7��
	init_data_blk(&data_r);
	init_data_blk(&cmp);
	init_data_blk(&out[0]);
	init_data_blk(&out[1]);
	int addr = 501;
	int joinnum = 0;


	for(i=0; i<4; i++){
		init_data_blk(&data_s[i]);
	}
	for(k=301; k<=316; k++){
		blk_r = readBlockFromDisk(k, buf);
		read_data_blk(blk_r, &data_r);

		for (j=0; j<7; j++){
			cmp.X[4] = data_r.X[j];
			if(data_r.X[j]<=19)
				continue;

			cmp.Y[4] = data_r.Y[j];

			for(i=0; i<4; i++){
				flag[i] = 0;
				pointer[i] = 0;
			}
			//data_blk data_s[4];
			for(i=0; i<4; i++){
				blk_s[i] = readBlockFromDisk(117+i*8, buf);
				group[i] = 1;
			}
            //�ȽϿ��еıȽ�
			while(!flag[0]||!flag[1]||!flag[2]||!flag[3]){
                //�ȽϿ��һ�α���
				//һ��������ˣ���Ҫ����
				for(i=0; i<4; i++){
					if(pointer[i]==7){
						if (group[i]<8){
							freeBlockInBuffer(blk_s[i], buf);
							blk_s[i] = readBlockFromDisk(i*8+group[i]+117, buf);
							pointer[i] = 0;
						}
						group[i]++;
					}
				}

				//������һ��������п鵱Ȼ��Ϊ1
				for(i=0; i<4; i++){
					if(group[i]>8)
						flag[i]=1;
				}

				int index[4];	//��¼��һ��S������R����
				for(i=0; i<=3; i++){
					index[i] = -1;
				}
				for(i=0; i<=3; i++){
					if(!flag[i]){
						read_data_blk(blk_s[i], &data_s[i]);
						int pos = pointer[i];
						cmp.X[i] = data_s[i].X[pos];
						cmp.Y[i] = data_s[i].Y[pos];
						pointer[i] ++;

						if(cmp.X[i]>cmp.X[4])
							flag[i]=1;
						else if(cmp.X[i]==cmp.X[4]){
							index[i] = 1;
							joinnum ++;
						}
						else
							continue;
					}
				}
				write_data_blk(compare, cmp);

				for(i=0; i<=3; i++){
					if(!flag[i]&&index[i]==1){
						if(outnum<=2){
							out[0].X[outnum*2] = cmp.X[4];
							out[0].Y[outnum*2] = cmp.Y[4];
							out[0].X[outnum*2+1] = cmp.X[i];
							out[0].Y[outnum*2+1] = cmp.Y[i];
						}
						else if(outnum==3){
							out[0].X[6] = cmp.X[4];
							out[0].Y[6] = cmp.Y[4];
							out[1].X[0] = cmp.X[i];
							out[1].Y[0] = cmp.Y[i];
						}else{
							out[1].X[2*outnum-7] = cmp.X[4];
							out[1].Y[2*outnum-7] = cmp.Y[4];
							out[1].X[2*outnum-6] = cmp.X[i];
							out[1].Y[2*outnum-6] = cmp.Y[i];
						}
						outnum ++;
						//�����д����

						if(outnum==7){
							out[0].addr = addr+1;
							out[1].addr = addr+2;

							/*
							for(int m=0; m<7; m++){
								printf("%d %d\n", out[0].X[m], out[0].Y[m]);
							}
							printf("%d\n\n", out[0].addr);
							for(int m=0; m<7; m++){
								printf("%d %d\n", out[1].X[m], out[1].Y[m]);
							}
							printf("%d\n\n", out[1].addr);
							*/

							write_data_blk(output[0], out[0]);
							write_data_blk(output[1], out[1]);
							init_data_blk(&out[0]);
							init_data_blk(&out[1]);
							outnum = 0;
							writeBlockToDisk(output[0], addr, buf);
							printf("ע�����д����̣�%d\n", addr);
							writeBlockToDisk(output[1], addr+1, buf);
							printf("ע�����д����̣�%d\n", addr+1);
							//��Ҫ��������
							output[0] = getNewBlockInBuffer(buf);
                            output[1] = getNewBlockInBuffer(buf);
							addr += 2;
						}
					}
				}
			}
			for(i=0; i<4; i++){
                freeBlockInBuffer(blk_s[i], buf);
            }
		}
		freeBlockInBuffer(blk_r, buf);
		init_data_blk(&data_r);
	}
	out[0].addr = 0;
	/*
	for(int m=0; m<7; m++){
        printf("%d %d\n", out[0].X[m], out[0].Y[m]);
    }
    printf("%d\n\n", out[0].addr);
	*/

    write_data_blk(output[0], out[0]);
    writeBlockToDisk(output[0], addr, buf);
    printf("ע�����д����̣�563\n\n");

	printf("�ܹ�����%d��\n\n", joinnum);
	freeBlockInBuffer(output[0], buf);
	freeBlockInBuffer(output[1], buf);
	freeBlockInBuffer(compare, buf);
	freeBlockInBuffer(blk_r, buf);

    return 0;
}


int func6(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("��������ļ��ϵĽ��㷨\n");
    printf("------------------------------------------------------------\n");
	unsigned char *blk_r, *compare;
	unsigned char *output;
	unsigned char *blk_s[4];
	int i, j, k;
	int group[4]; //Sÿ���Ѿ����˶��ٿ�
	int flag[4];	//���������Ϊ1������û����Ϊ0
	int pointer[4];	//Ŀǰ���ĸ�Ԫ��
	/*for(i=0; i<4; i++){
		flag[i] = 0;
		pointer[i] = 0;
	}*/
	data_blk data_s[4];
	/*for(i=0; i<4; i++){
		blk_s[i] = readBlockFromDisk(117+i*8, buf);
		group[i] = 1;
	}*/
	compare = getNewBlockInBuffer(buf);
	output = getNewBlockInBuffer(buf);
	data_blk data_r, cmp;
	data_blk out;
	int outnum = 0;	//��¼������Ѿ���¼�˶��ٸ�����
	init_data_blk(&data_r);
	init_data_blk(&cmp);
	init_data_blk(&out);
	int addr = 601;
	int internum = 0;


	for(i=0; i<4; i++){
		init_data_blk(&data_s[i]);
	}
	for(k=301; k<=316; k++){
		blk_r = readBlockFromDisk(k, buf);
		read_data_blk(blk_r, &data_r);

		for (j=0; j<7; j++){
			cmp.X[4] = data_r.X[j];
			if(data_r.X[j]<=19)
				continue;

			cmp.Y[4] = data_r.Y[j];

			for(i=0; i<4; i++){
				flag[i] = 0;
				pointer[i] = 0;
			}
			//data_blk data_s[4];
			for(i=0; i<4; i++){
				blk_s[i] = readBlockFromDisk(117+i*8, buf);
				group[i] = 1;
			}
            //�ȽϿ��еıȽ�
			while(!flag[0]||!flag[1]||!flag[2]||!flag[3]){
                //�ȽϿ��һ�α���
				//һ��������ˣ���Ҫ����
				for(i=0; i<4; i++){
					if(pointer[i]==7){
						if (group[i]<8){
							freeBlockInBuffer(blk_s[i], buf);
							blk_s[i] = readBlockFromDisk(i*8+group[i]+117, buf);
							pointer[i] = 0;
						}
						group[i]++;
					}
				}

				//������һ��������п鵱Ȼ��Ϊ1
				for(i=0; i<4; i++){
					if(group[i]>8)
						flag[i]=1;
				}

				int index[4];
				for(i=0; i<=3; i++){
					index[i] = -1;
				}
				for(i=0; i<=3; i++){
					if(!flag[i]){
						read_data_blk(blk_s[i], &data_s[i]);
						int pos = pointer[i];
						cmp.X[i] = data_s[i].X[pos];
						cmp.Y[i] = data_s[i].Y[pos];
						pointer[i] ++;

						if(cmp.X[i]>cmp.X[4])
							flag[i]=1;
						else if(cmp.X[i]==cmp.X[4]&&cmp.Y[i]==cmp.Y[4]){
							index[i] = 1;
							internum ++;
						}
						else
							continue;
					}
				}
				write_data_blk(compare, cmp);

				for(i=0; i<=3; i++){
					if(!flag[i]&&index[i]==1){
						out.X[outnum] = cmp.X[4];
						out.Y[outnum] = cmp.Y[4];
						outnum ++;
						//�����д����

						if(outnum==7){
							out.addr = addr+1;

							for(int m=0; m<7; m++){
								printf("(X=%d,Y=%d)\n", out.X[m], out.Y[m]);
							}

							write_data_blk(output, out);
							init_data_blk(&out);
							outnum = 0;
							writeBlockToDisk(output, addr, buf);
							printf("ע�����д����̣�%d\n", addr);
							//��Ҫ��������
							output = getNewBlockInBuffer(buf);
							addr += 1;
						}
					}
				}
			}
			for(i=0; i<4; i++){
                freeBlockInBuffer(blk_s[i], buf);
            }
		}
		freeBlockInBuffer(blk_r, buf);
		init_data_blk(&data_r);
	}

	out.addr = 0;
	for(int m=0; m<outnum; m++){
        printf("(X=%d,Y=%d)\n", out.X[m], out.Y[m]);
    }
    write_data_blk(output, out);
    writeBlockToDisk(output, addr, buf);
    printf("ע�����д����̣�%d\n\n", addr);

	printf("S��R�Ľ�����%d��Ԫ��\n\n", internum);
	freeBlockInBuffer(output, buf);
	freeBlockInBuffer(compare, buf);
	freeBlockInBuffer(blk_r, buf);
    return 0;
}


int func7(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("��������ļ��ϵĲ��㷨\n");
    printf("------------------------------------------------------------\n");

	unsigned char *blk_r, *compare;
	unsigned char *output;
	unsigned char *blk_s[4];
	int i, j, k;
	data_blk data_s[4];
	int addr = 701;
	int unionnum = 0;
	for(i=0; i<4; i++){
		init_data_blk(&data_s[i]);
	}

	//��ʼ��
	for(j=0; j<8; j++){
		for(i=0; i<4; i++){
			blk_s[i] = readBlockFromDisk(117+i*8+j, buf);
			read_data_blk(blk_s[i], &data_s[i]);
			for(int m=0; m<7; m++){
				printf("(X=%d,Y=%d)\n", data_s[i].X[m], data_s[i].Y[m]);
			}
			writeBlockToDisk(blk_s[i], addr, buf);
			printf("ע�����д����̣�%d\n", addr);
			addr++;
			unionnum+=7;
			freeBlockInBuffer(blk_s[i], buf);
		}
	}

	int group[4]; //Sÿ���Ѿ����˶��ٿ�
	int flag[4];	//���������Ϊ1������û����Ϊ0
	int pointer[4];	//Ŀǰ���ĸ�Ԫ��

	compare = getNewBlockInBuffer(buf);
	output = getNewBlockInBuffer(buf);
	data_blk data_r, cmp;
	data_blk out;
	int outnum = 0;	//��¼������Ѿ���¼�˶��ٸ�����
	init_data_blk(&data_r);
	init_data_blk(&cmp);
	init_data_blk(&out);

	for(i=0; i<4; i++){
		init_data_blk(&data_s[i]);
	}
	for(k=301; k<=316; k++){
		blk_r = readBlockFromDisk(k, buf);
		read_data_blk(blk_r, &data_r);

		for (j=0; j<7; j++){
			cmp.X[4] = data_r.X[j];
			int hit = 0;
			if(data_r.X[j]<=19)
				hit = 0;
			cmp.Y[4] = data_r.Y[j];

			for(i=0; i<4; i++){
				flag[i] = 0;
				pointer[i] = 0;
			}
			//data_blk data_s[4];
			for(i=0; i<4; i++){
				blk_s[i] = readBlockFromDisk(117+i*8, buf);
				group[i] = 1;
			}
            //�ȽϿ��еıȽ�
			while(!flag[0]||!flag[1]||!flag[2]||!flag[3]){
                //�ȽϿ��һ�α���
				//һ��������ˣ���Ҫ����
				for(i=0; i<4; i++){
					if(pointer[i]==7){
						if (group[i]<8){
							freeBlockInBuffer(blk_s[i], buf);
							blk_s[i] = readBlockFromDisk(i*8+group[i]+117, buf);
							pointer[i] = 0;
						}
						group[i]++;
					}
				}

				//������һ��������п鵱Ȼ��Ϊ1
				for(i=0; i<4; i++){
					if(group[i]>8)
						flag[i]=1;
				}

				for(i=0; i<=3; i++){
					if(!flag[i]){
						read_data_blk(blk_s[i], &data_s[i]);
						int pos = pointer[i];
						cmp.X[i] = data_s[i].X[pos];
						cmp.Y[i] = data_s[i].Y[pos];
						pointer[i] ++;

						if(cmp.X[i]>cmp.X[4])
							flag[i]=1;
						else if(cmp.X[i]==cmp.X[4]&&cmp.Y[i]==cmp.Y[4]){
							hit = 1;
						}
						else
							continue;
					}
				}
				write_data_blk(compare, cmp);
			}
			for(i=0; i<4; i++){
                freeBlockInBuffer(blk_s[i], buf);
            }

			if(hit==0){
				unionnum++;
				out.X[outnum] = cmp.X[4];
				out.Y[outnum] = cmp.Y[4];
				outnum++;
				if(outnum==7){
					out.addr = addr+1;

					for(int m=0; m<7; m++){
						printf("(X=%d,Y=%d)\n", out.X[m], out.Y[m]);
					}

					write_data_blk(output, out);
					init_data_blk(&out);
					outnum = 0;
					writeBlockToDisk(output, addr, buf);
					printf("ע�����д����̣�%d\n", addr);
					//��Ҫ��������
					output = getNewBlockInBuffer(buf);
					addr += 1;
				}
			}
		}
		freeBlockInBuffer(blk_r, buf);
		init_data_blk(&data_r);
	}

	out.addr = 0;
	for(int m=0; m<outnum; m++){
        printf("(X=%d,Y=%d)\n", out.X[m], out.Y[m]);
    }
    write_data_blk(output, out);
    writeBlockToDisk(output, addr, buf);
    printf("ע�����д����̣�%d\n\n", addr);
	printf("S��R�Ĳ�����%d��Ԫ��\n\n", unionnum);
	freeBlockInBuffer(output, buf);
	freeBlockInBuffer(compare, buf);
	freeBlockInBuffer(blk_r, buf);
    return 0;
}


int func8(Buffer *buf){
	printf("------------------------------------------------------------\n");
    printf("��������ļ��ϵĲ��㷨R-S\n");
    printf("------------------------------------------------------------\n");
	unsigned char *blk_r, *compare;
	unsigned char *output;
	unsigned char *blk_s[4];
	int i, j, k;
	int group[4]; //Sÿ���Ѿ����˶��ٿ�
	int flag[4];	//���������Ϊ1������û����Ϊ0
	int pointer[4];	//Ŀǰ���ĸ�Ԫ��
	/*for(i=0; i<4; i++){
		flag[i] = 0;
		pointer[i] = 0;
	}*/
	data_blk data_s[4];
	/*for(i=0; i<4; i++){
		blk_s[i] = readBlockFromDisk(117+i*8, buf);
		group[i] = 1;
	}*/
	compare = getNewBlockInBuffer(buf);
	output = getNewBlockInBuffer(buf);
	data_blk data_r, cmp;
	data_blk out;
	int outnum = 0;	//��¼������Ѿ���¼�˶��ٸ�����
	init_data_blk(&data_r);
	init_data_blk(&cmp);
	init_data_blk(&out);
	int addr = 801;
	int diffnum = 0;

	for(i=0; i<4; i++){
		init_data_blk(&data_s[i]);
	}
	for(k=301; k<=316; k++){
		blk_r = readBlockFromDisk(k, buf);
		read_data_blk(blk_r, &data_r);

		for (j=0; j<7; j++){
			cmp.X[4] = data_r.X[j];
			int hit = 0;
			if(data_r.X[j]<=19)
				hit = 0;
			cmp.Y[4] = data_r.Y[j];

			for(i=0; i<4; i++){
				flag[i] = 0;
				pointer[i] = 0;
			}
			//data_blk data_s[4];
			for(i=0; i<4; i++){
				blk_s[i] = readBlockFromDisk(117+i*8, buf);
				group[i] = 1;
			}
            //�ȽϿ��еıȽ�
			while(!flag[0]||!flag[1]||!flag[2]||!flag[3]){
                //�ȽϿ��һ�α���
				//һ��������ˣ���Ҫ����
				for(i=0; i<4; i++){
					if(pointer[i]==7){
						if (group[i]<8){
							freeBlockInBuffer(blk_s[i], buf);
							blk_s[i] = readBlockFromDisk(i*8+group[i]+117, buf);
							pointer[i] = 0;
						}
						group[i]++;
					}
				}

				//������һ��������п鵱Ȼ��Ϊ1
				for(i=0; i<4; i++){
					if(group[i]>8)
						flag[i]=1;
				}

				for(i=0; i<=3; i++){
					if(!flag[i]){
						read_data_blk(blk_s[i], &data_s[i]);
						int pos = pointer[i];
						cmp.X[i] = data_s[i].X[pos];
						cmp.Y[i] = data_s[i].Y[pos];
						pointer[i] ++;

						if(cmp.X[i]>cmp.X[4])
							flag[i]=1;
						else if(cmp.X[i]==cmp.X[4]&&cmp.Y[i]==cmp.Y[4]){
							hit = 1;
						}
						else
							continue;
					}
				}
				write_data_blk(compare, cmp);
			}
			for(i=0; i<4; i++){
                freeBlockInBuffer(blk_s[i], buf);
            }

			if(hit==0){
				diffnum++;
				out.X[outnum] = cmp.X[4];
				out.Y[outnum] = cmp.Y[4];
				outnum++;
				if(outnum==7){
					out.addr = addr+1;
					for(int m=0; m<7; m++){
						printf("(X=%d,Y=%d)\n", out.X[m], out.Y[m]);
					}
					write_data_blk(output, out);
					init_data_blk(&out);
					outnum = 0;
					writeBlockToDisk(output, addr, buf);
					printf("ע�����д����̣�%d\n", addr);
					//��Ҫ��������
					output = getNewBlockInBuffer(buf);
					addr += 1;
				}
			}
		}
		freeBlockInBuffer(blk_r, buf);
		init_data_blk(&data_r);
	}

	out.addr = 0;
	for(int m=0; m<outnum; m++){
        printf("(X=%d,Y=%d)\n", out.X[m], out.Y[m]);
    }
    write_data_blk(output, out);
    writeBlockToDisk(output, addr, buf);
    printf("ע�����д����̣�%d\n\n", addr);
	printf("R-S��%d��Ԫ��\n\n", diffnum);
	freeBlockInBuffer(output, buf);
	freeBlockInBuffer(compare, buf);
	freeBlockInBuffer(blk_r, buf);
	return 0;
}


int main(int argc, char **argv)
{
    Buffer buf; /* A buffer */

    /* Initialize the buffer */
    if (!initBuffer(520, 64, &buf))
    {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }

    while(1){
        int choice = menu();
        switch(choice)
        {
            case 1:
            {
				func1(&buf);
                continue;
            }
            case 2:
            {
                tpmms(&buf);
                continue;
            }
			case 3:
			{
				setindex(&buf);
				func3(&buf);
				continue;
			}
			case 4:
			{
				func4(&buf);
				continue;
			}
			case 5:
            {
                func5(&buf);
                continue;
            }
            case 6:
            {
                func6(&buf);
                continue;
            }
			case 7:
			{
				func7(&buf);
				continue;
			}
			case 8:
			{
				func8(&buf);
				continue;
			}
            case 0:
            {
                freeBuffer(&buf);
                return 0;
            }
            default:
                continue;
        }
    }

}

