//----------------------------------------------------------------------------------------
//	Copyright © 2016 - 2017 Neumantec Solutions LLP.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class provides the logic to simulate Java rectangular arrays, which are jagged
//	arrays with inner arrays of the same length.
//----------------------------------------------------------------------------------------

#ifndef __NEUMANTEC_ARRAY_H__
#define __NEUMANTEC_ARRAY_H__

#include<iostream>
using namespace std;

// Row Major implemenation of 2D-Array for C++
template<class T>
class Array
{
public:
    // A helper class to Wrap the pointer that points to the begiining of each row and allow array indexing within the row.
    class Row {
    public:
        Row(T* _array, unsigned _length) : m_array(_array), m_length(_length) { }

        ~Row() {
        	m_array = NULL;
        	m_length = 0;
        }

        T& operator[](int index) {
            return m_array[index];
        }
        
        // Java-like length method to return the length of each row, same as 2nd dim(number of cols).
        unsigned length(){
        	return m_length;
        }

    private:
        T* m_array;
        unsigned m_length;
    };
    
    Array(unsigned rows=1, unsigned cols=1): m_rows(rows), m_cols(cols) {
        m_rowArray = NULL;
        if (m_rows > 0)
        {
            m_rowArray = new T*[m_rows];
            if (m_cols > 0)
            {
                // Allocate r*c elements as 1 array, instead of allocating 1 array per row.
                m_rowArray[0] = new T[m_rows * m_cols];
                for (unsigned row = 1; row < m_rows; row++)
                {
                    // Manipulate each subsequent row pointer to point to the correct posiytion in the array.
                    m_rowArray[row] = m_rowArray[0] + row * m_cols;
                }
            }
        }
    }
    
    ~Array() {
        if (m_rowArray && m_rows > 0)
        {
            delete[] m_rowArray[0]; // Free the entire r*c chunk.
            delete[] m_rowArray;    // Free the list of pointers to rows.
            m_rowArray = NULL;
            m_rows = 0;
            m_cols = 0;
        }
    }
    
    friend ostream &operator<<( ostream &output, const Array &arr ) {
    	output<<"\t";
    	for(unsigned c=0; c < arr.m_cols; c++) {
    		output<<"["<<c+1<<"]\t";
    	}
    	output<<endl;
    	
    	for(unsigned row=0; row < arr.m_rows; row++) {
    		output<<"["<<row+1<<"]\t";
    		for(unsigned col=0; col < arr.m_cols; col++) {
    			output<<" "<<arr.m_rowArray[row][col]<<"\t";
    		}
    		output<<endl;
    	}
    	return output;
    }
    
    // Java-like length method to return the length of the 2D-array, same as the 1st dim (number of rows).
    unsigned length() { 
        return m_rows; 
    }
    
    Row operator[](int index) {
    	return Row(m_rowArray[index], m_cols);
    }

private:
    unsigned int m_rows, m_cols;
    T** m_rowArray;
};

#endif //__NEUMANTEC_ARRAY_H__