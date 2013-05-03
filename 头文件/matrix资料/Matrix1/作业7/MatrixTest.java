class Matrix{
	 int rows,cols;
	 int data[][];
	 Matrix(){}
	 Matrix(int rows,int cols)
	 {
           this.rows=rows;
           this.cols=cols;
           data=new int[rows][cols];
	 }
         Matrix(int rows,int cols,int data[][])
         {
      	   this.rows=rows;
  	   this.cols=cols;
  	   this.data=data;
         }
 
         int getData(int row,int col)
         {
          return data[row][col];	
         }
         int setData(int row,int col,int value)
         {
  	  data[row][col]=value;
  	  return value;
         }  	       
  
         Matrix multiply(Matrix m)
         {
    	  int i,j,k;
  	  Matrix result=new Matrix(rows,m.cols);
  	  for(i=0;i<rows;i++)
  	    for(j=0;j<m.cols;j++)
  	     for(k=0;k<cols;k++)
  	       result.data[i][j]+=data[i][k]*m.data[k][j];
  	  return result;
         }
  
          public String toString()
          {
  	      String result="";
  	      for(int i=0;i<rows;i++){
  	   	for(int j=0;j<cols;j++)
  	   	   result+=+data[i][j]+"  ";
  	        result+="\n";
  	        }
  	      return result;
  	  }

	 void Fuzhi(int rows,int cols)
	 {
	  int i,j;
	  for(i=0;i<rows;i++)
            for(j=0;j<cols;j++)
              data[i][j]=(int)(Math.random()*10);
	 }	
}

public class MatrixTest{
        public static void main(String[] args){
           int i,j,a,b,x,y;
           System.out.print("输入矩阵A的行数:");
           a=KeyInput.readInt();
           System.out.print("输入矩阵A的列数:");
           b=KeyInput.readInt();
           Matrix A=new Matrix(a,b);
           A.Fuzhi(a,b);
           System.out.println("***矩阵A***\n"+A.toString());
           
           System.out.print("输入矩阵B的行数:");
           x=KeyInput.readInt();
           System.out.print("输入矩阵B的列数:");
           y=KeyInput.readInt();
           Matrix B=new Matrix(x,y);
           B.Fuzhi(x,y);
           System.out.println("***矩阵B***\n"+B.toString());
           
           if(b!=x)
    	     System.out.println("不符合矩阵相乘条件,不能相乘!");
    	   else
             System.out.println("相乘结果为:\n"+A.multiply(B).toString());
         }
}