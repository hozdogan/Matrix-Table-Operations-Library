#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

template <class T>
class Matrix
{
	public:
		Matrix(int ,int,const T&);
		Matrix();
		int rows();
		int cols();
		void print();
		void print(char*);
		float det();
		Matrix& inv();
		T& getElem(int,int);
		void resize(int ,int);
		void setElem(int ,int,const T&);
		Matrix& transpose();
		Matrix* emul(Matrix*);
		Matrix& emul(Matrix&);
	
		Matrix& operator+(Matrix&);
		Matrix& operator-(Matrix&);
		Matrix& operator*(Matrix&);
		
		Matrix* operator*(Matrix*);
		Matrix* operator+(Matrix*);
		Matrix* operator-(Matrix*);
		
		Matrix& operator+(T);
		Matrix& operator-(T);
		Matrix& operator*(T);
		Matrix& operator%(T);
		Matrix& operator/(T);
		Matrix& operator^(T);
		
	private:
		T** mat;
		int row,col;
		T elem;
		float deter(T**,int);
		T** inverse(T**,int);
			
};






template <class T>
class Table:public Matrix<T>
{
	public:
		Table(int ,int,const T&);
		Table();
		T& itemAt(int,int);
		T& itemAt(string);
		T& itemAt(string,string);
		void print();
		void setRowNames(string [],int);
		void setColNames(string [],int);
		void setRowName(string,int);
		void setColName(string,int);
	private:
		T** mat;
		int row,col;
		T elem;		
		string* colNames;
		string* rowNames;
};


struct RGB
{
	int r,g,b;	
};

template <class T>
class image:public Matrix<int>
{
	public:
		image(int ,int);
		image();
		void print();
		void color2Gray();
		void binary(int);	
	private:
		T** mat;
		int row,col;
		T elem;		

};

template<class T>
void image<T>::print()
{
	for(int i = 0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout<<mat[i][j].r<<"\t";
		}
		cout<<"\n"<<endl;
	}
}

template<class T>
image<T>::image(int row,int col)
{
	this->row = row;
	this->col = col;
	mat = new T*[row];
	for(int i = 0;i<row;i++)
	{
		mat[i] = new T[col];
	}	
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			mat[i][j].r = 180;
			mat[i][j].g = 180;
			mat[i][j].b = 180;
		}
	}
}


template<class T>
image<T>::image()
{
	this->row = 255;
	this->col = 255;
	mat = new T*[row];
	for(int i = 0;i<row;i++)
	{
		mat[i] = new T[col];
	}	
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)	
		{
			mat[i][j].r = 0;
			mat[i][j].g = 0;
			mat[i][j].b = 0;
				
		}
		
	}
}

template <class T>
void image<T>::color2Gray()
{
	int gray;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			gray = (mat[i][j]->r*0.3)+(mat[i][j]->g*0.59)+(mat[i][j]->b*0.11);
			mat[i][j].r = gray;
			mat[i][j].g = gray;
			mat[i][j].b = gray;
		}
	}
}

template <class T>
void image<T>::binary(int thres)
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
				if(mat[i][j].r < thres)
				{
					mat[i][j].r = 0;
					mat[i][j].g = 0;
					mat[i][j].b = 0;
				}
				else if(mat[i][j].r>thres)
				{
					mat[i][j].r = 255;
					mat[i][j].g = 255;
					mat[i][j].b = 255;
				}
			
			
		}
	}
}



template <class T>
Table<T>::Table(int row,int col ,const T& t):Matrix<T>(row,col,t)
{
	
	this->row = row;
	this->col = col;
	elem = t;
	mat = new T*[row];
	for(int i = 0;i<row;i++)
	{
		mat[i] = new T[col];
	}
		
	if(t == 'e')
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				if(i == j)
				{
					mat[i][j] = 1;
				}
				else
					mat[i][j] = 0;
			}
		}
	}
	else if(t == 'r')
	{
		srand(time(NULL));
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				mat[i][j] = rand()%256;
			}
		}
		
	}
	else
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				mat[i][j] = t;
			}
		}
	}
	colNames = new string[col];
	rowNames = new string[row];
	
	for(int i=0;i<row;i++)
	{
		rowNames[i] = "";
	}
	for(int i=0;i<col;i++)
	{
		colNames[i] = "";
	}
	for(int i=0;i<row;i++)
	{
		ostringstream oss;
		oss<<i;
		rowNames[i] = oss.str();
	}
	for(int i=0;i<col;i++)
	{
		if(i<26)
		{
		  colNames[i]+=65+i; 
		}
		else
		{
		  colNames[i] = "";
		}
	}
	
}
template<class T>		
Table<T>::Table():Matrix<T>()
{
	this->row = 10;
	this->col = 10;
	this->elem = 0;
	mat = new T*[row];
	for(int i=0;i<row;i++)
	{
		mat[i] = new T[col];
	}
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			mat[i][j] = 0;
		}
	}
	
	colNames = new string[col];
	rowNames = new string[row];
	for(int i=0;i<row;i++)
	{
		rowNames[i] = "";
	}
	for(int i=0;i<col;i++)
	{
		colNames[i] = "";
	}
	for(int i=0;i<row;i++)
	{
		ostringstream oss;
		oss<<i;
		rowNames[i] = oss.str();
	}
	for(int i=0;i<col;i++)
	{
		if(i<26)
		{
		  colNames[i]+=65+i;
		}
		else
		{
		  colNames[i]="";
		}
	}
}

template <class T>
T& Table<T>::itemAt(int r,int c)
{
	return mat[r][c];
}

template<class T>
T& Table<T>::itemAt(string s)
{
	const char* ch = s.c_str();
	int c = (int)ch[0]-65;
    const char* ch2 = s.substr(1,s.length()).c_str(); 
	int r = atoi(ch2);
	return mat[r][c];
}

template<class T>
T& Table<T>::itemAt(string rs,string cs)
{
	int r1,c1;
	for(int i=0;i<row;i++)
	{
		if(rs.compare(rowNames[i]) == 0)
		{
			r1 = i;
			break;
		}
	}
	for(int j=0;j<col;j++)
	{
		if(cs.compare(colNames[j]) == 0)
		{
			c1 = j;
			break;
		}
		
	}
	return mat[r1][c1];
}

template<class T>
void Table<T>::print()
{
	//Matrix<T>::print();
	string **s = new string*[row+2];
	for(int i=0;i<row+2;i++)
	{
		s[i] = new string[col+2]; 
	} 
	for(int i=1;i<row+1;i++)
	{
		 s[i][0] = this->rowNames[i-1];	
	}
	for(int j=1;j<col+1;j++)
	{
		s[0][j] = this->colNames[j-1];
	}
	for(int i=1;i<row+1;i++)
	{
		for(int j=1;j<col+1;j++)
		{
			ostringstream oss;
			oss<<this->mat[i-1][j-1];
			s[i][j] = oss.str();
			
		}
	}
	
	for(int i = 0;i<row+1;i++)
	{
		for(int j=0;j<col+1;j++)
		{
			cout<<s[i][j]<<"\t";
		}
		cout<<"\n"<<endl;
	}
	
	
}

template <class T>
void Table<T>::setRowNames(string s[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(s[i].length()>8)
			return;
	}
	for(int i=0;i<n;i++)
	{
		this->rowNames[i] = s[i];
	}
}

template <class T>
void Table<T>::setColNames(string s[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(s[i].length()>4)
			return;
	}
	for(int i=0;i<n;i++)
	{
		this->colNames[i] = s[i];
	}
}

template <class T>
void Table<T>::setColName(string s,int n)
{
	this->colNames[n] = s;
}

template <class T>
void Table<T>::setRowName(string s,int n)
{
	this->rowNames[n] = s;
}











template <class T>
Matrix<T>::Matrix()
{
	elem = 0;
	this->row = 10;
	this->col = 10;
	mat = new T*[row];
	for(int i=0;i<row;i++)
	{
		mat[i] = new T[col];
	}
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			mat[i][j] = 0;
		}
	}
}
template <class T>
Matrix<T>::Matrix(int r,int c,const T& t)
{
	row = r;
	col = c;
	elem = t;
	mat = new T*[r];
	for(int i = 0;i<r;i++)
	{
		mat[i] = new T[c];
	}
		
	if(t == 'e')
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				if(i == j)
				{
					mat[i][j] = 1;
				}
				else
					mat[i][j] = 0;
			}
		}
	}
	else if(t == 'r')
	{
		srand(time(NULL));
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				mat[i][j] = rand()%256;     // random degerleri ile oynama
			}
		}
		
	}
	else if(t == 'L')
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				mat[i][j] = i*col+j;
			}
		}
	}
	else
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				mat[i][j] = t;
			}
		}
	}
}
template <class T>
int Matrix<T>::cols()
{
	return col;
}
template <class T>
int Matrix<T>::rows()
{
	return row;
}
template <class T>
void Matrix<T>::resize(int a,int b)    //o an girilen elemanlari koyuyoruz
{
	T temp[row][col];
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				temp[i][j] = mat[i][j];
			}
		}
		mat = new T*[a];
		for(int i=0;i<a;i++)
		{	
			mat[i] = new T[b];
		}
		for(int i=0;i<a;i++)
		{
			for(int j=0;j<b;j++)
			{
				mat[i][j] = 0;
			}
		}
		if(a>row&&b<col)
			col = b;
		else if(a<row&&b>col)
			row = a;
		else if(a<this->row && b <this->col)
		{
			row = a;
			col = b;
		}
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				mat[i][j] = temp[i][j];
			}
		}
		row = a;
		col = b;
}
template <class T>
void Matrix<T>::print()    //burda oynadýk
{
	for(int i = 0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout<<mat[i][j]<<"\t";
		}
		cout<<"\n"<<endl;
	}
}
template <class T>
T& Matrix<T>::getElem(int row,int col)
{
	if(this->row<row||this->col<col)
	{
		exit(1);
	}
	else if(this->row<0 || this->col<0)
	{
		exit(1);
	}
	return mat[row][col];
}
template <class T>
void Matrix<T>::setElem(int r,int c,const T& el)
{
	if(row<r||col<c)
	{
		return;
	}
	else if(r<0 || c<0)
	{
		return;
    }
	mat[r][c] = el;
}

template <class T>
Matrix<T>& Matrix<T>::operator+(Matrix& m1)
{
	if(this->rows() != m1.rows() || this->cols() != m1.cols())
	{
		exit(1);
	}
	Matrix<T> m2(m1.rows(),m1.cols(),0);
	for(int row = 0;row<m1.rows();row++)
	{
		for(int col=0;col<m2.cols();col++)
		{
			m2.setElem(row,col,this->getElem(row,col)+m1.getElem(row,col));
		}
	}
	return m2;
}
template <class T>
Matrix<T>& Matrix<T>::operator-(Matrix& m1)
{
	if(this->rows() != m1.rows() || this->cols() != m1.cols())
	{
		exit(1);
	}
	Matrix<T> m2(m1.rows(),m1.cols(),0);
	for(int row = 0;row<m1.rows();row++)
	{
		for(int col=0;col<m2.cols();col++)
		{
			m2.setElem(row,col,this->getElem(row,col)-m1.getElem(row,col));
		}
	}
	return m2;
}

template <class T>
Matrix<T>& Matrix<T>::operator*(Matrix& m1)
{
	int temp = 0;
	if(m1.rows() != this->cols())
	{
		return m1;
	}
	Matrix<T> m2(this->rows(),m1.cols(),0);
	
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<m1.cols();col++)
		{
			for(int k=0;k<this->cols();k++)
			{
				temp += (int)this->getElem(row,k)*(int)m1.getElem(k,col);
			}
			m2.setElem(row,col,(T)temp);
			temp = 0;
		}
	}
	return m2;
}

//dynamic object 
template <class T>
Matrix<T>* Matrix<T>::operator*(Matrix* m1)
{
	int temp = 0;
	if(m1->rows() != this->cols())
	{
		exit(1);
	}
	//Matrix<T> m2(this->rows(),m1.cols(),0);
	Matrix<T> *m2 = new Matrix<int>(this->rows(),m1->cols(),0);
	
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<m1->cols();col++)
		{
			for(int k=0;k<this->cols();k++)
			{
				temp += (int)this->getElem(row,k)*(int)m1->getElem(k,col);
			}
			m2->setElem(row,col,(T)temp);
			temp = 0;
		}
	}
	return m2;
}



template <class T>
Matrix<T>* Matrix<T>::operator-(Matrix* m1)
{
	if(this->rows() != m1->rows() || this->cols() != m1->cols())
	{
		exit(1);
	}
	Matrix<T> *m2 = new Matrix<int>(m1->rows(),m1->cols(),0);
	for(int row = 0;row<m1->rows();row++)
	{
		for(int col=0;col<m2->cols();col++)
		{
			m2->setElem(row,col,this->getElem(row,col)-m1->getElem(row,col));
		}
	}
	return m2;
}


template <class T>
Matrix<T>* Matrix<T>::operator+(Matrix* m1)
{
	if(this->rows() != m1->rows() || this->cols() != m1->cols())
	{
		exit(1);
	}
	Matrix<T> *m2 = new Matrix<int>(m1->rows(),m1->cols(),0);
	for(int row = 0;row<m1->rows();row++)
	{
		for(int col=0;col<m2->cols();col++)
		{
			m2->setElem(row,col,this->getElem(row,col)+m1->getElem(row,col));
		}
	}
	return m2;
}




//overloading
template <class T>
Matrix<T>& Matrix<T>::operator+(T c1)
{
	T t = 0.0f;
	//Matrix<T> m2(this->rows(),this->cols(),0);
	Matrix<T> *m2 = new Matrix<T>(this->rows(),this->cols(),t);
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<this->cols();col++)
		{
			m2->setElem(row,col,this->getElem(row,col)+c1);
		}
	}
	return *m2;
}

template <class T>
Matrix<T>& Matrix<T>::operator-(T c1)
{
	T t = 0.0f;
	Matrix<T> *m2 = new Matrix<T>(this->rows(),this->cols(),t);
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<this->cols();col++)
		{
			m2->setElem(row,col,this->getElem(row,col)-c1);
		}
	}
	return *m2;
}

template <class T>
Matrix<T>& Matrix<T>::operator*(T c1)
{
	T t= 0.0f;
	
	Matrix<T> *m2 = new Matrix<T>(this->rows(),this->cols(),t);
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<this->cols();col++)
		{
			m2->setElem(row,col,this->getElem(row,col)*c1);
		}
	}
	return *m2;
}

template <class T>
Matrix<T>& Matrix<T>::operator%(T c1)
{
	T t = 0.0;
	Matrix<T> *m2 = new Matrix<T>(this->rows(),this->cols(),t);
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<this->cols();col++)
		{
			m2->setElem(row,col,this->getElem(row,col)%c1);
		}
	}
	return *m2;
}

template <class T>
Matrix<T>& Matrix<T>::operator/(T c1)
{
	T t = 0.0f;
	Matrix<T> *m2 = new Matrix<T>(this->rows(),this->cols(),t);
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<this->cols();col++)
		{
			m2->setElem(row,col,this->getElem(row,col)/c1);
		}
	}
	return *m2;
}


template <class T>
Matrix<T>& Matrix<T>::operator^(T c1)
{
	T t = 0.0f;
	Matrix<T> *m2 = new Matrix<T>(this->rows(),this->cols(),t);
	for(int row = 0;row<this->rows();row++)
	{
		for(int col=0;col<this->cols();col++)
		{
			m2->setElem(row,col,pow(this->getElem(row,col),c1));
		}
	}
	return *m2;
}



template <class T>
Matrix<T>& Matrix<T>::transpose()
{
	Matrix<T> *mT = new Matrix<T>(this->cols(),this->rows(),0);
	for(int i = 0;i<this->rows();i++)
	{
		for(int j=0;j<this->cols();j++)
		{
			mT->setElem(j,i,this->getElem(i,j));
		}
	}
	return *mT;
}


template <class T>
Matrix<T>& Matrix<T>::emul(Matrix& m1)
{
	Matrix<T> mM(this->rows(),this->cols(),0);
	for(int i = 0;i<this->rows();i++)
	{
		for(int j=0;j<this->cols();j++)
		{
			mM.setElem(i,j,this->getElem(i,j)*m1.getElem(i,j));
		}
	}
	return mM;
}

template <class T>
Matrix<T>* Matrix<T>::emul(Matrix* m1)
{
	Matrix<T> *mM = new Matrix<int>(this->rows(),this->cols(),0);
	for(int i = 0;i<this->rows();i++)
	{
		for(int j=0;j<this->cols();j++)
		{
			mM->setElem(i,j,this->getElem(i,j)*m1->getElem(i,j));
		}
	}
	return mM;
}

template<class T>
void Matrix<T>::print(char* path)
{
	ofstream dosya;
	dosya.open(path);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			dosya<<mat[i][j]<<"\t";
		}
		dosya<<endl;
	}
	dosya.close();
	cout<<"Matris dosyaya yazildi"<<endl;
}

template <class T>
float Matrix<T>::deter(T** m1,int n)
{
	int count = 0,temp;
	float det=0;
	T* one_dimension_temp = new T[(n-1)*(n-1)];
	T** two_dimension_temp = new T*[n-1];
	for(int j=0;j<n-1;j++)
	{
		two_dimension_temp[j] = new T[n-1];
	}
	
	if(n == 2)
	{
		det = (m1[0][0]*m1[1][1]) - (m1[0][1]*m1[1][0]);
		return det;
	}
	else if(n > 2)
	{
		for(int i=0;i<n;i++)
		{
			for(int row=0;row<n;row++)	
			{
				for(int col=0;col<n;col++)
				{
					if(row == 0 || col == i)
					{
						continue;
					}
					else
					{	
						one_dimension_temp[count] = m1[row][col];
						count++;					
					}
				}		
			}
			count = 0;
			for(int row=0;row<n-1;row++)	
			{
				for(int col=0;col<n-1;col++)
				{
					temp = row*(n-1)+col;
					two_dimension_temp[(temp-col)/(n-1)][col] = one_dimension_temp[temp];		
				}
			}
			if(i%2 == 1)
			{
				m1[0][i]*=-1;
			}
			det += m1[0][i] * deter(two_dimension_temp,n-1);
		}
	}
	return det;
}

template <class T>
float Matrix<T>::det()
{
	 return deter(mat,row);
}

template <class T>
Matrix<T>& Matrix<T>::inv()
{
	T** temp1 = new T*[this->rows()];
	for(int i=0;i<this->rows();i++)
	{
		temp1[i] = new T[this->cols()];
	}
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			temp1[i][j] = mat[i][j];
		}	
	}
	 temp1 = inverse(temp1,row);
	Matrix<T> *mI = new Matrix<T>(this->rows(),this->cols(),0);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			mI->setElem(i,j,temp1[i][j]);
		}	
	}
	return *mI;
}
template <class T>
T** Matrix<T>::inverse(T** m1,int n)
{
	float d,k,temp,det;
	T** unit_matris = new T*[n];
	for(int i=0;i<n;i++)
	{
		unit_matris[i] = new T[n];
	}
	if(n < 2)
	{
		exit(-1);
	}
	else if(n == 2)
	{
		det = this->deter(m1,2);
		m1[0][1]*=-1;
		m1[1][0]*=-1;
		temp = m1[0][0];
		m1[0][0] = m1[1][1];
		m1[1][1] = temp;
		for(int row=0;row<n;row++)
		{
			for(int col=0;col<n;col++)
			{
				m1[row][col]/=det;			
			}
		}
		return m1;
	}
	else
	{
		for(int row=0;row<n;row++)
		{
			for(int col=0;col<n;col++)
			{
				if(row == col)
				{
					unit_matris[row][col] = 1.0f;
				}
				else
				{
					unit_matris[row][col] = 0.0f;
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			d = m1[i][i];
			for(int j=0;j<n;j++)
			{
				m1[i][j]/=d;
				unit_matris[i][j]/=d;
			}
				for(int x=0;x<n;x++)
				{
					if(x!=i)
					{
						k=m1[x][i];
						for(int l=0;l<n;l++)
						{
							m1[x][l] -= (m1[i][l]*k);
							unit_matris[x][l] -= (unit_matris[i][l]*k);
						}
					}
				}
		}
		
		return unit_matris;	
	}
}






int main() {
/*
  Adýmlar ve kurallar
    0. Kendi saatinden en az 10dk önce savunma yerinde hazýr bulun ve sýra sana geldiðinde gösterilen bilgisayara otur
    1. Depodan kendi öðrenci numaranýn olduðu kodu bul,
    2. Gerekirse dosyanýn uzantýsýný cpp yap,
    3. kendi main içindeki kodu sil ve aþaðýdaki örnek senaryoyu main içerisine kopyala
    4. "sec" deðiþkenini 1-10 arasý deðerler vererek her bir durumu dene
    5. gerekirse kodda çok küçük deðiþiklikler yapýlabilir.
    6. kodu "gcc", "g++" gibi bir derleyicide derle ve çalýþtýr.

*/

 Matrix<double> a(2,3,1.);
 Matrix<double> b(2,3,9.);
 Matrix<double> m1(4,4,'e');
      Matrix<double> m2(4,4,'r'); // (5,5) boyutu dene
      Matrix<double> m3(5,4,1);
       Matrix<double> m4(2,2,'L');
      Matrix<double> m5 = m4 * m4.inv();
     
      Matrix<double> m6(3,3,'L');
      Table<int> t1(4,4,1);
       Table<int> t2(3,4,'r');
        string s[] = {"Sat1","Sat2"};
        string s2[] = {"S1","S2","S3"};
  int sec = 4;
  
  switch(sec){
    case 1 :
      //Matrix<double> a(2,3,1.);
      a.print();
      //Matrix<double> b(2,3,9.);
      b.print();
      a = b + a*1;
      a.print("file.txt"); // içinde 10 olan matris olmalý
      break;
    case 2 :
     // Matrix<double> m1(4,4,'e');
      //Matrix<double> m2(4,4,'r'); // (5,5) boyutu dene
      m2.print();
      m1 = m1 * m2;
      m1.print();
      break;
    case 3 :
      // STL vector kullanan buradan puan alamaz
      //Matrix<double> m3(5,4,1);
      m3.print();
      // aþaðýdaki durumlarý ayrý ayrý dene
      //m3.resize(2,6);
      //m3.resize(10,6);
      m3.resize(10,3);

      m3.print();
      break;
    case 4 :
      // lineer matris oluþtur
      //Matrix<double> m4(2,2,'L');
      m4.print();
      
      //Matrix<double> m5 = m4 * m4.inv();
      m5.print(); // birim matris olmalý

      //Matrix<double> m6(3,3,'L');
      cout<<m6.det(); // sonuç 0 olmalý
      break;
    case 5 :
    /*
      Image tanýmý:
      class Image:public Matrix<RGB> þeklinde olmalý

      Image içerisinde matris verisi, geniþlik, yükseklik olmayacak
    */
      break;
    case 6 :
      //Image im1("custom.bin");
     // im1.threshold(128);
      //im1.print("custom2.bin");
      break;
    case 7 :
     // Image im2("imfile.bmp");
     // im2.print("imfile2.bmp");
      break;
    case 8 :
     ///Image im3("custom.bin");
     // im3.threshold(128);
      //im3.erosion();
      //im3.print("custom2.bin");
      break;
    case 9 :
      /*
      Matrix sýnýfýndan miras alýnacak,
      matris, geniþlik, yükseklik verisi Table sýnýfý içinde olmayacak, miras alýnacak
      */
     // Table<int> t1(4,4,1);
      t1.print(); // satýr ve sütun etiketleri de yazýlmalý
      //string s = {"Sat1","Sat2"};
      t1.setRowNames(s,2);
      t1.print();
      break;
    case 10 :
      //Table<int> t2(3,4,'r');
      t2.print();
      cout<<t2.itemAt(1,1)<<endl; // (1,1) deki eleman
      cout<<t2.itemAt("A2")<<endl;  // (2,0) deki eleman
      //string s2 = {"S1","S2","S3"};
      t2.setColNames(s2,3);
      cout<<t2.itemAt("1","S2")<<endl;  // (1,1) deki eleman
      break;
    default:
    	cout<<"olmadi"<<endl;
  }
}
