#include <iostream>
#include <vector>
//https://www.cnblogs.com/onepixel/articles/7674659.html
//终端输出改变颜色： https://blog.csdn.net/wangxudongx/article/details/88178112
//基类
class Sort{
  public:	
	Sort(){};
	~Sort(){};
	virtual void sort(std::vector<int> vec){};
	virtual void print(const std::vector<int>& vec){
		int len=vec.size();
		for(int i=0;i<len;++i){
			std::cout<<vec[i]<<" ";
		}    
		std::cout<<";"<<std::endl;
	}
	void swap(std::vector<int>& vec,int i,int j){
		int temp=vec[i];
		vec[i]=vec[j];
		vec[j]=temp;
	}
	void swap(int& a,int& b){
		int temp=a;
		a=b;
		b=temp;
	}
	void check(const std::vector<int>& vec){
		int len=vec.size();
		for(int i=0;i<len-1;++i){
			if(vec[i]>vec[i+1]){
				printf("\033[31mCheck: Sorry!!! Sorted failed! The failed indices is %d and %d!\n\033[0m",i,i+1);
				return;
			}
		}
		printf("\033[32mChecked: Congratulations!!! Sorted Successfully!\n\033[0m");
	} 
};
//1.冒泡排序
class BubbleSort: public Sort {
  public:
	BubbleSort(){};
	~BubbleSort(){};
	virtual void sort(std::vector<int> vec){
		printf("before bubble sort:\n");
		print(vec);
		int len=vec.size();
		int temp;
		for(int i=0;i<len-1;++i){
			for(int j=0;j<len-1-i;++j){
				if(vec[j]>vec[j+1]){
					temp=vec[j];
					vec[j]=vec[j+1];
					vec[j+1]=temp;
				}
			}
		}
		printf("after bubble sort:\n");
		print(vec);
		check(vec);
	}
	
};
//2.选择排序
class SelectionSort: public Sort {
  public:
	SelectionSort(){};
	~SelectionSort(){};
	void sort(std::vector<int> vec){
		printf("before selection sort:\n");
		print(vec);
		int len=vec.size();
		int temp,minidx;
		for(int i=0;i<len;++i){
			minidx=i;
			for(int j=i;j<len;++j){
				if(vec[minidx]>vec[j])
					minidx=j;
			}
			temp=vec[i];
			vec[i]=vec[minidx];
			vec[minidx]=temp;

		}
		printf("after selection sort:\n");
		print(vec);
		check(vec);
	}
	
};
//3.插入排序
class InsertionSort: public Sort {
  public:
	InsertionSort(){};
	~InsertionSort(){};
	void sort(std::vector<int> vec){
		printf("before insertion sort: \n");
		print(vec);
		int len=vec.size();
		int current;
		for(int i=1;i<len;++i){
			current=vec[i];
			for(int j=i-1;j>=0;--j){
				if(current<vec[j]){
					vec[j+1]=vec[j];
					vec[j]=current;
				}else{
					break;
				}

			}
		}
		printf("after insertion sort: \n");
		print(vec);
		check(vec);
	}
};
//4.希尔排序(缩小增量排序)
//TODO:原理未理解
class ShellSort: public Sort {
  public: 
	ShellSort(){};
	~ShellSort(){};
	void sort(std::vector<int> vec){
		printf("before Shell sort: \n");
		print(vec);
		int len=vec.size();
		if(len<2)
			return;
		for(int gap=len/2;gap>0;gap=gap/2){	
			for(int i=gap;i<len;++i){
				int current=vec[i];
				for(int j=i;j-gap>=0 && current< vec[j-gap];j-=gap){
					vec[j]=vec[j-gap];
					vec[j-gap]=current;
				}
			}
		}
		printf("after Shell sort: \n");
		print(vec);
		check(vec);

	}
};
//5.归并排序
class MergeSort: public Sort {
  public:
	MergeSort(){};
	~MergeSort(){};
	void sort(std::vector<int> vec){
		printf("before merge sort: \n");
		print(vec);
		vec=sort_vec(vec);
		printf("after merge sort: \n");
		print(vec);
		check(vec);
	}
	std::vector<int> sort_vec(std::vector<int> vec){
		int len=vec.size();
		if(len<2)
			return vec;
		int midlen=len/2;
		std::vector<int> left(vec.begin(),vec.begin()+midlen);
		std::vector<int> right(vec.begin()+midlen,vec.end());
		return merge(sort_vec(left),sort_vec(right));
	}
	std::vector<int> merge(std::vector<int> left, std::vector<int> right){
		std::vector<int> res;
		res.reserve(left.size()+right.size());
		int left_idx=0;
		int right_idx=0;
		while(left_idx<left.size() && right_idx<right.size()){
			if(left[left_idx]<right[right_idx]){
				res.emplace_back(left[left_idx]);
				++left_idx;
			}else{
				res.emplace_back(right[right_idx]);
				++right_idx;
			}
		}
		while(left_idx<left.size()){
			res.emplace_back(left[left_idx]);
			++left_idx;
		}
		while(right_idx<right.size()){
			res.emplace_back(right[right_idx]);
			++right_idx;
		}
		return res;
	}
};
//6.快速排序
//另一种形式的归并排序？
class QuickSort: public Sort {
  public:
	int count=0;
	QuickSort(){};
	~QuickSort(){};
	void sort(std::vector<int> vec){
		printf("before quick sort: \n");
		print(vec);
		quick_sort(vec);		
		printf("after quick sort: \n");
		print(vec);
		check(vec);
	}
	//sort_nums=1,2,4,8,16...
	void quick_sort(std::vector<int>& vec){
		int len=vec.size();
		if(len<2)
			return;
		int sort_nums=1;
		while(sort_nums<vec.size()){
			for(int i=0;i<vec.size();i+=2*sort_nums){
				int left_start=i;
				int left_end=left_start+sort_nums;
				int right_start=left_end;
				int right_end=right_start+sort_nums>vec.size()?vec.size():right_start+sort_nums;
				// std::cout<<count++<<" "<<left_start<<" "<<left_end<<" "<<right_end<<std::endl;
				for(int right_idx=right_start; right_idx<right_end;++right_idx){
					int current=vec[right_idx];
					int temp;
					for(int left_idx=right_idx-1;left_idx>=left_start;--left_idx){
						// std::cout<<"current: "<<current<<" vec["<<left_idx<<"]: "<<vec[left_idx]<<std::endl;
						if(current<vec[left_idx]){
							temp=vec[left_idx+1];
							vec[left_idx+1]=vec[left_idx];
							vec[left_idx]=current;
						}else{
							break;
						}
						// print(vec);

					}
				}
			}
			sort_nums*=2;
		}
	}


};
//7.堆排序
/**
 * 堆积采用完全二叉树概念，将待排序数列等效为数组[0,1,2,3,4,5,6,7,...,n]
 * 二叉树性质：
 * 1. 空二叉树高度为-1
 * 2. 第k层，最多有2^k个节点
 * 3. 高度（深度）为k的二叉树，节点至多有2^(k+1)-1个
 * 4. 第k层，第一个节点或叶子，数组的索引为2^(k+1)-1
 * 5. 设第i-1层，第k个节点的有左、右两个child,(0<=k<2^(i-1)),
 * 	  该节点的索引是：2^i-1+k=m
 * 	  left child的数组索引为 left_idx=2^(i+1)+2k-1=2*(2^i-1+k)+1=2m+1
 * 	  right child的数组索引为 right_idx=2^(i+1)+2k=2*(2^i-1+k)+2=2m+2
 * 6. 长度为len的数组，完美二叉树的深度为 deep=(len+1)/2-1
 * 7. 长度为len的数组，最大节点索引为: idx=len/2-1
 * 大顶堆积：
 * 1. 具有n个数据元素的序列 K = (k0, k1, k2, k3, k4, . . . , kn); 
 * 2. 当且仅当满足条件 k[i]>=k[i*2+1] && k[i]>=k[i*2+2]; i = (0, 1, 2, 3, 4, . . . , n/2)
 * 小顶堆积：
 * 1. 具有n个数据元素的序列 K = (k0, k1, k2, k3, k4, . . . , kn); 
 * 2. 当且仅当满足条件 k[i]<=k[i*2+1] && k[i]<=k[i*2+2]; i = (0, 1, 2, 3, 4, . . . , n/2)
 **/
class HeapSort: public Sort {
  public:
	HeapSort(){};
	~HeapSort(){};
	void sort(std::vector<int> vec){
		printf("before Heap Sort: \n");
		print(vec);
		len=vec.size();
		// std::vector<int> res(len,0);
		while(len>1){
			heap_sort(vec,len);
			temp=vec[0];
			vec[0]=vec[len-1];
			vec[len-1]=temp;
			--len;
		}
		printf("after Heap Sort: \n");
		print(vec);   
		check(vec);

	}
	void heap_sort(std::vector<int>& vec, int& len){
		if(len<2)
			return;
		int i=len/2-1; //最大非叶子节点的索引；
		//处理边界值
		if(len%2==1){
			if(vec[2*i+2]>vec[i]){
				temp=vec[i];
				vec[i]=vec[2*i+2];
				vec[2*i+2]=temp;
			}
		}
		if(vec[2*i+1]>vec[i]){
			temp=vec[2*i+1];
			vec[2*i+1]=vec[i];
			vec[i]=temp;
		}
		//处理非边界值
		for(int j=i-1;j>=0;--j){
			if(vec[2*j+2]>vec[j]){
					temp=vec[2*j+2];
					vec[2*j+2]=vec[j];
					vec[j]=temp;
			}
			if(vec[2*j+1]>vec[j]){
				temp=vec[2*j+1];
				vec[2*j+1]=vec[j];
				vec[j]=temp;
			}
		}

	}
	int len;
	int temp;

};
//8.计数排序
class CountingSort: public Sort {
  public:
	CountingSort(){};
	~CountingSort(){};
	void sort(std::vector<int> vec){
		printf("before counting sort: \n");
		print(vec);
		int min,max;
		min=max=vec[0];
		int len=vec.size();
		if(len<2)
			return;
		// std::cout<<min<<" "<<max<<" "<<vec[0]<<std::endl;
		//查找最大值、最小值
		for(int i=0;i<len;++i){
			if(vec[i]>max)
				max=vec[i];
			else if(vec[i]<min)
				min=vec[i];
		}
		//建立计数数组
		std::vector<int> count(max-min+1,0);
		for(int i=0;i<len;++i){
			++count[vec[i]-min];
		}
		vec.clear();
		for(int i=0;i<count.size();++i){
			while(count[i]>0){
				vec.emplace_back(i+min);
				--count[i];
			}
		}
		printf("after counting sort: \n");
		print(vec);
		check(vec);
	}

};
//9.桶排序
//类似计数排序，知道数值的具体范围比较好；
class BucketSort: public Sort {
  public:
	BucketSort(){
		quick_sort=new QuickSort;
	}
	~BucketSort(){
		delete quick_sort;
	}
	void sort(std::vector<int> vec){
		printf("befort bucket sort: \n");
		print(vec);
		//暂时设定0~1000，知道最大值、最小值，能设计更合理的桶、及分桶规则；
		// int bucket_size=100;
		// int bucket_num=10;
		// int bucket_idx,bucket_element_idx;
		// std::vector<std::vector<int>> res(bucket_num);
	/*
		std::vector<std::vector<int>> res(bucket_num,std::vector<int>(bucket_size,0));
		//分桶，这个方法不适用于负数
		for(int i=0;i<vec.size();++i){
			bucket_idx=vec[i]/bucket_size;
			bucket_element_idx=vec[i]%bucket_size;
			++res[bucket_idx][bucket_element_idx];
		}
		//反向填充
		int idx=0;
		for(int i=0;i<bucket_num;++i){
			for(int j=0;j<bucket_size;++j){
				while(res[i][j]!=0){
					vec[idx]=i*bucket_size+j;
					++idx;
					--res[i][j];
				}
			}
		}
	*/
		int bucket_num=8;
		int bucket_idx;
		std::vector<std::vector<int>> res(bucket_num);
		//分桶
		for(int i=0;i<vec.size();++i){
			bucket_idx=vec[i]%bucket_num;
			if(bucket_idx<0)
				bucket_idx=-1*bucket_idx;
			res[bucket_idx].emplace_back(vec[i]);
		}
		// print(res[0]);
		// //桶内快速排序
		for(int i=0;i<bucket_num;++i){
			bool flag=false;
			std::cout<<"i: "<<i<<std::endl;
			print(res[i]);
			while(res[i].size()==0){
				res.erase(res.begin()+i);
				--bucket_num;
				if(i>=bucket_num){
					flag=true;
					break;
				}
			}
			if(flag)
				break;
			quick_sort->quick_sort(res[i]);
		}
		printf("after delete: \n");
		for(int i=0;i<bucket_num;++i){
			std::cout<<"i: "<<i<<std::endl;
			print(res[i]);
		}
		std::cout<<"bucket_num0: "<<bucket_num<<std::endl;
		printf("11111111111111111111111111111\n");
		std::vector<int> temp;
		int count=0,bucket_num_temp;
		int vec_idx=vec.size()-1;
		while(bucket_num>0){
			temp.clear();
			for(int i=0;i<bucket_num;++i){
				printf("after delete i=%d\n",i);
				print(res.at(i));
				temp.emplace_back(res[i].back());
				res[i].pop_back();
			}
			print(temp);

			quick_sort->quick_sort(temp);
			for(auto it=temp.rbegin();it!=temp.rend();++it){
				vec[vec_idx]=*it;
				printf("paixu: idx=%d,value=%d\n",vec_idx,vec[vec_idx]);
				--vec_idx;
			}
			if(bucket_num==bucket_num_temp){
				++count;
				if(count>2)
					exit(0);
			}
			bucket_num_temp=bucket_num;
			//删除空桶
			for(int i=0;i<bucket_num;++i){
				bool flag=false;
				std::cout<<"i: "<<i<<std::endl;
				print(res[i]);
				while(res[i].size()==0){
					res.erase(res.begin()+i);
					--bucket_num;
					if(i>=bucket_num){
						flag=true;
						break;
					}
				}
			}
		}

		printf("after bucket sort: \n");
		print(vec);
		check(vec);
	}

  private:
	QuickSort* quick_sort;
};
//10.基数排序
//TODO:

int main(int argc, char const *argv[])
{
	/* code */
	std::vector<std::vector<int>> test_vec;
	std::vector<int> test0{-10,20,16,1,1,4,7,6,3,5,2,4,100,9,9,11,5};
	test_vec.emplace_back(test0);
	std::vector<int> test1{1,4};
	test_vec.emplace_back(test1);
	std::vector<int> test2{4,1};
	test_vec.emplace_back(test2);
	std::vector<int> test3{4};

	Sort* bubble_sort=new BubbleSort;
	Sort* selection_sort=new SelectionSort;
	Sort* insertion_sort=new InsertionSort;
	Sort* shell_sort=new ShellSort;
	Sort* merge_sort=new MergeSort;
	Sort* quick_sort=new QuickSort;
	Sort* heap_sort=new HeapSort;
	Sort* counting_sort=new CountingSort;
	Sort* bucket_sort=new BucketSort;
	for(int i=0;i<test_vec.size();++i){
		bubble_sort->sort(test_vec[i]);		
		selection_sort->sort(test_vec[i]);
		insertion_sort->sort(test_vec[i]);
		shell_sort->sort(test_vec[i]);
		merge_sort->sort(test_vec[i]);
		quick_sort->sort(test_vec[i]);
		heap_sort->sort(test_vec[i]);
		counting_sort->sort(test_vec[i]);
		// bucket_sort->sort(test_vec[i]); //still has some problems;
	}
	return 0;
};