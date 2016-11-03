#include <iostream>
#include "cls.h"
using namespace std;

int main()
{
    Matrix<double> md={
    {1,2,3,4,5},
    {6,7,8,9},
    {1},
    {1,2,3},
    {1,2,3,1,2}
    };
    Matrix<double> sm={
        {1,0,0},
        {0},
        {0}
    };

    cout
    <<"md itself\n"<<md<<endl
    <<"md+md=\n"<<md+md<<endl
    <<"md-md=\n"<<md-md<<endl
    <<"md*3=\n"<<md*3.0<<endl
    <<"2*md=\n"<<2.0*md<<endl
    <<"md*md=\n"<<md*md<<endl
    <<"det(md)=\n"<<md.determinant()<<endl;


    cout<<"md^(-1)=\n"<<md.inverse()<<endl;
    md.eraseColumn(1);
    md.eraseRow(1);
    cout<<"md after erase()\n"<<md<<endl;
    cout<<"det(md)=\n"<<md.determinant()<<endl;
    cout<<"inverse of a singular matrix\n"<<sm.inverse()<<endl;

    cout<<"tr(md)=\n"<<md.trace()<<endl;
    md.insertColumn(1,Matrix<double>::Vector({1,2,3,4,5}));
    cout<<"md after insert()\n"<<md<<endl;
    Matrix<double>::Vector v1{1,2,3,4,5},v2{2,2,2,2,2};
    cout<<"iterating a vector"<<endl;
    for(auto x:v1){
        cout<<x<<" ";
    }
    cout<<"\nvector size=\n"<<v1.size()<<endl;
    cout<<"<v1,v2>=\n"<<v1.innerProduct(v2)<<endl;
    cout<<"md(1,1)"<<endl<<md[1][1]<<endl;
    cout<<"iterating a matrix"<<endl;
    for(auto r:md){
        for(auto x:r){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    cout<<"an unitary matrix\n"<<E<double>(5)<<endl;
    Matrix<double> e5=E<double>(5);
    e5(1,3)=5;
    cout<<"after changing an element\n"<<e5<<endl;
    e5.addRow(Matrix<double>::Vector({1,3,1,4,2}));
    cout<<"after adding a row\n"<<e5<<endl;
    e5.addColumn(Matrix<double>::Vector({1,3,1,4,2}));
    cout<<"after adding a column\n"<<e5;
    Matrix<double> em;
    em.addColumn(v1);
    em.addRow(v2);
    cout<<"adding elements to an empty matrix\n"<<em<<endl;
    cout<<"md\n"<<md<<endl
    <<"(md)^T\n"<<md.transpose()<<endl
    <<"md row="<<md.numRow()<<" md column="<<md.numColumn()<<endl
    <<"t row="<<md.transpose().numRow()<<" t column="<<md.transpose().numColumn()<<endl;
    cout<<"\n!!!!!!!!!!!!\nNow testing int matrix"<<endl;
    Matrix<int> mi={
        {1,2},
        {1,2,3},
        {1,2,3,4,5},
        {1,1,2,1,2},
        {1}
    };
    cout<<mi<<endl
    <<mi.determinant()<<endl
    <<mi.trace()<<endl
    <<mi.inverse()<<endl
    <<mi.transpose()<<endl
    <<(mi*=mi)<<endl;
    return 0;
}

