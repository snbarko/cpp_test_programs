#include <iostream>
#include <vector>

using namespace std;

class MyMatrix
{
public:
    MyMatrix():row(0), column(0)
    {
    }

    MyMatrix(int _row, int _column): row(_row), column(_column)
    {
        cout << "row " << row << " column " << column << " " << __LINE__ << endl;
        if ((_row == 0) || (_column == 0))
        {
            cout << "Welcome to matrix constructor" << endl;
            cout << "Enter number of rows: ";
            cin >> row;
            cout << "Enter number of columns: ";
            cin >> column;
        }
        data = new int*[row];
        for (int i = 0; i < row; i++)
        {
            data[i] = new int[column];
            if ((_row == 0) || (_column == 0))
            {
                for (int j = 0; j < column; j++)
                {
                    cout << "Enter data for row " << i << " column " << j << std::endl;
                    cin >> data[i][j];
                }
            }
        }
    }
public:
    MyMatrix& operator+(std::vector<MyMatrix>& vec)
    {
        for (int i = 0;i < vec.size(); i++)
        {
            (*this) = (*this) + vec[i];
        }
        return (*this);
    }
    
    MyMatrix& operator+(MyMatrix& _matrix)
    {
        if ((this->getRow() == 0) || (this->getColumn() == 0))
        {
            allocateData(_matrix.getRow(), _matrix.getColumn());
        }
        if ((this->getRow() != _matrix.getRow()) ||
            (this->getColumn() != _matrix.getColumn()))
        {
            cout << "Matrices has different orders. Addition not possible" << this->getRow() << this->getColumn() << endl;
            return (*this);
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                data[i][j]+= *(*(_matrix.data + i) + j);
            }
        }

        return (*this);
    }

    friend ostream& operator<<(ostream& os, MyMatrix& _matrix)
    {
        os << "Printing matrix: " << "row " << _matrix.getRow() << " " << _matrix.getColumn() << endl;
        for (int i = 0; i < _matrix.getRow(); i++)
        {
            for (int j = 0; j < _matrix.getColumn(); j++)
            {
                os << *(*(_matrix.getData() + i) + j) << " ";
            }
            os << std::endl;
        }
        return os;
    }
    
    MyMatrix& operator+(int data)
    {
        for (int i = 0; i < this->getRow(); i++)
        {
            for (int j = 0; j < this->getColumn(); j++)
            {
                *(*(this->data + i) + j) = *(*(this->data + i) + j) + data;
            }
        }

        return (*this);
    }

    friend MyMatrix& operator+(int data, MyMatrix& inmatrix)
    {
        for (int i = 0; i < inmatrix.getRow(); i++)
        {
            for (int j = 0; j < inmatrix.getColumn(); j++)
            {
                *(*(inmatrix.data + i) + j) = *(*(inmatrix.data + i) + j) + data;
            }
        }

        return inmatrix;
    }

    int** getData() { return data; }
    int getRow() { return row; }
    int getColumn() { return column; }

private:
    void allocateData(int _row, int _column)
    {
        row = _row;
        column = _column;
        data = new int*[row];
        for (int i = 0; i < row; i++)
        {
            data[i] = new int[column];
        }
    }
    int row;
    int column;
    int **data;
};

int main()
{
    int num = 0;
    std::cout << "How many matrices ? ";
    std::cin >> num;
    {
        std::vector<MyMatrix> myMatrixArray;
        MyMatrix sumMatrix;

        for (int i = 0;i < num; i++)
        {
            myMatrixArray.push_back(MyMatrix(0,0));
            cout << myMatrixArray[i];
        }
        sumMatrix = sumMatrix + myMatrixArray;
        // sumMatrix = myMatrixArray + sumMatrix;
        cout << sumMatrix;
        sumMatrix = 5 + sumMatrix;
        cout << sumMatrix;
        sumMatrix = sumMatrix + 7;
        cout << sumMatrix;
        sumMatrix = 10 + sumMatrix + 100;
        cout << sumMatrix;
    }

    return 0;
}
