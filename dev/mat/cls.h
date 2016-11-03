#include <bits/stdc++.h>
template <class TVal>
struct Result{
    bool good;
    TVal val;
    Result(bool b,TVal t):good(b),val(t){};
    operator bool(){
        return good;
    }
    operator TVal(){
        return val;
    }
};
template <class TVal>
struct Matrix{
    std::vector<std::vector<TVal>> mat;
    bool good;
    size_t nColumn;

    using _row=std::vector<TVal>;
    using _column=std::vector<TVal>;

    int sign(std::vector<int> &vi,int x){
        int n=1;
        for(int i=0;i<x;i++){
            if(vi[i]>vi[x]){
                n=-n;
            }
        }
        return n;
    }
public:
    template <class Tval>
    friend std::ostream& operator<<(std::ostream&,Matrix<Tval> &);
    template <class Tval>
    friend std::ostream& operator<<(std::ostream &o,Matrix<Tval> &&x);

    struct Vector{
        private:
            std::vector<TVal> r;
        public:
            bool isColumnVector;
            friend class Matrix<TVal>;
            TVal operator[](size_t n){return r[n-1];}
            typename std::vector<TVal>::iterator begin(){return r.begin();}
            typename std::vector<TVal>::iterator end(){return r.end();}
            size_t size(){return r.size();}
            Vector(std::vector<TVal> &v,bool cv=false):r(v),isColumnVector(cv){};
            Vector(std::initializer_list<TVal>  &&listx,bool cv=false):r(listx),isColumnVector(cv){};
            Result<TVal> innerProduct(Vector &v2){
                if(v2.size()!=r.size()){
                    return Result<TVal>(false,0);
                }
                TVal res=0;
                for(size_t x=0;x<v2.size();x++){
                    res+=r[x]*v2.r[x];
                }
                return Result<TVal>(true,res);
            }
        };

    using rowIter=typename std::vector<TVal>::iterator;
    using columnIter=typename std::vector<std::vector<TVal>>::iterator;

    ~Matrix()=default;

    Matrix():good(true),nColumn(0){};
    Matrix(size_t row,size_t column):nColumn(column),mat(row,_row(column,(TVal)0)),good(true){};
    Matrix& operator=(Matrix&&)=default;
    Matrix(Matrix const&)=default;
    Matrix& operator=(Matrix const&)=default;
    TVal& operator()(size_t i,size_t j){
        return mat[i-1][j-1];
    }
    Matrix& operator=(bool x){
        good=x;
        if(!good)
            nColumn=0;
        return *this;
    }
    Matrix& operator=(std::vector<std::vector<TVal>> &xmat){
        mat=xmat;
        good=true;
        if(xmat.empty()){
            nColumn=0;
        }
        nColumn=xmat[0].size();
        return *this;
    }
    Matrix(std::initializer_list<std::initializer_list<TVal>> mx){
        nColumn=0;
        for(auto m:mx){
            _row newr;
            for(auto mi:m){
                newr.push_back(mi);
            }
            if(nColumn<newr.size())
                nColumn=newr.size();
            mat.push_back(newr);
            for(auto it=mat.begin();it<mat.end();it++){
                while(it->size()<nColumn)
                {
                    it->push_back(0);
                }
            }
        }
        good=true;
    }
    Vector operator[](size_t x){
        return Vector(mat[x-1]);
    }
    bool insertRow(size_t n,const  Vector &rx){
        if(!good)
            return false;
        if(n>=mat.size()){
            return false;
        }
        _row nr=rx.r,r=rx.r;
        if(nColumn<nr.size()){
            nColumn=r.size();
            for(auto it=mat.begin();it<mat.end();it++){
                while(it->size()<nColumn){
                    it->push_back(0);
                }
            }
        }
        while(nr.size()<nColumn){
            nr.push_back(0);
        }
        mat.insert(mat.begin()+n-1,nr);
        return true;
    }
    bool insertColumn(size_t n,const Vector &cx){
        if(!good)
            return false;
        size_t i=0;
        const _column &c=cx.r;
        if(n>=nColumn){
            return false;
        }
        _row newr(nColumn,0);
        while(c.size()>mat.size()){
            mat.push_back(newr);
        }
        for(auto it=mat.begin();it!=mat.end();it++,i++){
            if(i<c.size()){
                it->insert(it->begin()+n-1,c[i]);
            }
            else{
                it->insert(it->begin()+n-1,0);
            }
        }
        nColumn++;
        return true;
    }
    bool eraseRow(size_t i){
        return eraseRow(i,i+1);
    }
    bool eraseRow(size_t i,size_t j){
        if(i>=mat.size()||j<i||j>=mat.size()){
            return false;
        }
        mat.erase(mat.begin()+i-1,mat.begin()+j-1);
        return true;
    }
    bool eraseColumn(size_t i,size_t j){
        if(i>nColumn||j>nColumn||j<i){
            return false;
        }
        for(auto it=mat.begin();it<mat.end();it++){
            it->erase(it->begin()+i-1,it->begin()+j-1);
        }
        nColumn+=i-j;
        return true;
    }
    bool eraseColumn(size_t i){
        return eraseColumn(i,i+1);
    }
    void addRow(const Vector &rx){
        if(mat.size()==0){
            nColumn=rx.r.size();
            mat.push_back(rx.r);
            return;

        }
        if(nColumn<rx.r.size()){
            auto nsize=rx.r.size();
            for(auto it=mat.begin();it!=mat.end();it++){
                while(it->size()<nsize)it->push_back((TVal)0);
            }
            nColumn=nsize;
            mat.push_back(rx.r);
        }
        else{
            auto vx=rx.r;
            while(vx.size()<nColumn){
                vx.push_back((TVal)0);
            }
            mat.push_back(vx);
        }
        nColumn++;
    }
    void addColumn(const Vector &cx){
        if(mat.empty()){
            nColumn=1;
            for(auto it:cx.r){
                mat.push_back(_row(1,it));
            }
            return;
        }
        auto cxr=cx.r;
        while(mat.size()<cxr.size()){
            mat.push_back(_row(nColumn,(TVal)0));
        }
        while(cxr.size()<mat.size()){
            cxr.push_back((TVal)0);
        }
        for(auto it=mat.begin(),itx=cxr.begin();it!=mat.end();it++,itx++){
            it->push_back(*itx);
        }
        nColumn++;
    }
    typename decltype(mat)::iterator begin(){return mat.begin();}
    typename decltype(mat)::iterator end(){return mat.end();}
    Matrix operator+(const Matrix &m2){

        Matrix<TVal> mres;
        if(!(good&&m2.good))
        {
            return mres=false;
        }
        if(m2.mat.size()!=this->mat.size()||m2.nColumn!=this->nColumn){
            return mres=false;
        }
        for(size_t i=0;i<mat.size();i++){
            _row newr;
            for(size_t j=0;j<mat[i].size();j++){
                newr.push_back(mat[i][j]+m2.mat[i][j]);
            }
            mres.mat.push_back(newr);
        }
        mres.nColumn=mres.mat[0].size();
        return mres=true;
    }
    template<class Tval>
    friend Matrix operator*(const Matrix<Tval> &thisx ,Tval val){
        Matrix<TVal> mres;
        if(!thisx.good){
            return mres=false;
        }
        for(auto r:thisx.mat){
            _row newr;
            for(auto i:r){
                newr.push_back(i*val);
            }
            mres.mat.push_back(newr);
        }
        mres.nColumn=mres.mat[0].size();
        return mres=true;
    }
    template<class Tval>
    friend Matrix operator*(Tval val,const Matrix<Tval> &thisx ){
        Matrix<TVal> mres;
        if(!thisx.good){
            return mres=false;
        }
        for(auto r:thisx.mat){
            _row newr;
            for(auto i:r){
                newr.push_back(i*val);
            }
            mres.mat.push_back(newr);
        }
        mres.nColumn=mres.mat[0].size();
        return mres=true;
    }
    Matrix operator-(const Matrix &m2){
        Matrix<TVal> mres;
        if(!(good&&m2.good))
        {
            return mres=false;
        }
        if(m2.mat.size()!=this->mat.size()||m2.nColumn!=this->nColumn){
            return mres=false;
        }
        for(size_t i=0;i<mat.size();i++){
            _row newr;
            for(size_t j=0;j<mat[i].size();j++){
                newr.push_back(mat[i][j]-m2.mat[i][j]);
            }
            mres.mat.push_back(newr);
        }
        mres.nColumn=mres.mat[0].size();
        return mres=true;
    }
    template <class Tval>
    friend Matrix operator*(Matrix<Tval> &m1,Matrix<Tval> &m2){
        Matrix<Tval> mres;
        if(!(m1.good&&m2.good)){
            return mres=false;
        }
        if(m1.nColumn!=m2.mat.size()){
            return mres=false;
        }
        for(size_t i=0;i<m1.mat.size();i++){
            _row newr;
            for(size_t j=0;j<m2.nColumn;j++){
                Tval ans=0;
                for(size_t k=0;k<m1.nColumn;k++){
                    ans+=m1.mat[i][k]*m2.mat[k][j];
                }
                newr.push_back(ans);
            }
            mres.mat.push_back(newr);
        }
        mres.nColumn=m2.nColumn;
        return mres=true;
    }
    Matrix& operator+=(Matrix x){
        (*this)=(*this)+x;
        return *this;
    }
    Matrix& operator-=(Matrix x){
        (*this)=(*this)-x;
        return *this;
    }
    Matrix& operator*=(TVal x){
        (*this)=(*this)*x;
        return *this;
    }
    Matrix& operator*=(Matrix x){
        (*this)=(*this)*x;
        return *this;
    }
    template <class Tval>
    friend Matrix<Tval> E(size_t n);
    Result<TVal> determinant(){
        if(nColumn!=mat.size()){
            return Result<TVal>(false,0);
        }
        std::vector<int> vi;
        TVal sum=0,tmp;
        for(int i=0;i<nColumn;i++)
            vi.push_back(i);
        do{
            tmp=1;
            for(int j=0;j<nColumn;j++){
                tmp*=sign(vi,j)*mat[j][vi[j]];
            }
            sum+=tmp;
        }while(next_permutation(vi.begin(),vi.end()));
        return Result<TVal>(true,sum);
    }
    Result<TVal> cofactor(size_t i,size_t j){
        Matrix<TVal> mres=*this;
        if(i>nColumn||j>nColumn||nColumn!=mat.size()){
            return Result<TVal>(false,0);
        }
        mres.eraseColumn(j);
        mres.eraseRow(i);
        if(mres.nColumn==0){
            return Result<TVal>(false,0);
        }
        return Result<TVal>(true,mres.determinant());
    }
    Result<TVal> algebraicCofactor(size_t i,size_t j){
        auto res=cofactor(i,j);
        if(!res){
            return res;
        }
        res.val*=(((i+j)%2)?(-1.0):1.0);
        return res;
    }
    Matrix<TVal> inverse(){
        Matrix<TVal> mres(nColumn,nColumn);
        if(nColumn!=mat.size()){
            return mres=false;
        }
        auto det=determinant();
        if(!det||!det.val){
            return mres=false;
        }
        for(size_t i=1;i<=mat.size();i++){
            for(size_t j=1;j<=nColumn;j++){
                mres.mat[j-1][i-1]=algebraicCofactor(i,j)?(algebraicCofactor(i,j).val/det.val):0;
            }
        }
        mres.nColumn=nColumn;
        return mres=true;
    }
    Result<TVal> trace(){
        if(nColumn!=mat.size()){
            return Result<TVal>(false,0);
        }
        TVal sum=0;
        for(size_t i=0;i<mat.size();i++){
            sum+=mat[i][i];
        }
        return Result<TVal>(true,sum);
    }
    Matrix transpose(){
        Matrix<TVal> mres;
        if(nColumn==0||mat.size()==0){
            return mres=false;
        }
        for(auto x:mat){
            mres.addColumn(Vector(x));
        }
        return mres;
    }
    size_t numRow(){return mat.size();}
    size_t numColumn(){return nColumn;}
};
template <class TVal>
std::ostream& operator<<(std::ostream &o,Matrix<TVal> &x){
    if(!x.good){
        return o<<"Invalid Value";
    }
    for(auto xi:x.mat){
        for(auto xj:xi){
            o<<std::setw(8)<<std::setprecision(2)<<xj;
        }
        o<<"\n";
    }
    return o;
}
template <class TVal>
std::ostream& operator<<(std::ostream &o,Matrix<TVal> &&x){
    if(!x.good){
        return o<<"Invalid Value";
    }
    for(auto xi:x.mat){
        for(auto xj:xi){
            o<<std::setw(8)<<std::setprecision(2)<<xj;
        }
        o<<"\n";
    }
    return o;
}
template <class TVal>
std::ostream& operator<<(std::ostream &o,Result<TVal> &&val){
    if(val){
        o<<val.val;
    }
    else{
        o<<"Invalid Value";
    }
    return o;
}
template <class TVal>
std::ostream& operator<<(std::ostream &o,Result<TVal> &val){
    if(val){
        o<<val.val;
    }
    else{
        o<<"Invalid Value";
    }
    return o;
}
template <class Tval>
Matrix<Tval> E(size_t n){
    Matrix<Tval> e(n,n);
    for(int i=1;i<=n;i++){
        e.mat[i-1][i-1]=(Tval)1;
    }
    return e;
}
