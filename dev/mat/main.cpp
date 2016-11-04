#include <iostream>
#include "cls.h"
using namespace std;
using namespace MCal;
int main()
{
    map<string,Matrix> ms;
    string cmd;
    while(cin>>cmd){
        if(cmd=="add"){
            string name;
            int i,j;
            cin>>name>>i>>j;
            if(!i||!j){
                cout<<"cannot add an empty matrix"<<endl;
                continue;
            }
            if(ms.find(name)!=ms.end()){
                cout<<"name already been used"<<endl;
                continue;
            }
            Matrix mtmp(i,j);
            for(int a=1;a<=i;a++){
                for(int b=1;b<=j;b++){
                    cin>>mtmp(a,b);
                }
            }
            ms[name]=mtmp;
            cout<<"add completed:"<<name<<endl<<mtmp
            <<"---------------------------------"<<endl;
        }
        else if(cmd=="delete"){
            string name;
            cin>>name;
            auto it=ms.find(name);
            if(it==ms.end()){
                cout<<"no such name"<<endl;
                continue;
            }
            cout<<"delete completed:"<<name<<endl<<it->second
            <<"---------------------------------"<<endl;
            ms.erase(it);
        }
        else if(cmd=="showall"){
            if(ms.empty()){
                cout<<"empty! please use add"<<endl;
            }
            for(auto x:ms){
                cout<<"matrix name:"<<x.first<<"\n---------------------------------"<<endl
                <<x.second<<"---------------------------------"<<endl;
            }
        }
        else if(cmd=="show"){
            string name;
            cin>>name;
            auto it=ms.find(name);
            if(it==ms.end()){
                cout<<"no such name"<<endl;
                continue;
            }
            cout<<"matrix name:"<<it->first<<"\n---------------------------------"<<endl
                <<it->second<<"---------------------------------"<<endl;
        }
        else if(cmd=="+"){
            string name1,name2,nres;
            cin>>name1>>name2>>nres;
            auto it1=ms.find(name1),it2=ms.find(name2),itres=ms.find(nres);
            if(it1==ms.end()){
                cout<<"there is no "<<name1<<endl;
                continue;
            }
            if(it2==ms.end()){
                cout<<"there is no "<<name2<<endl;
                continue;
            }
            if(itres!=ms.end()){
                cout<<"name "<<nres<<" already been used"<<endl;
                continue;
            }
            Matrix mres=(it1->second)+(it2->second);
            if(!mres){
                cout<<"cannot calculate "<<name1<<" + "<<name2<<endl;
                continue;
            }
            ms[nres]=mres;
            cout<<"calculation result:"<<nres<<endl<<mres<<"---------------------------------"<<endl;

        }
        else if(cmd=="-"){
            string name1,name2,nres;
            cin>>name1>>name2>>nres;
            auto it1=ms.find(name1),it2=ms.find(name2),itres=ms.find(nres);
            if(it1==ms.end()){
                cout<<"there is no "<<name1<<endl;
                continue;
            }
            if(it2==ms.end()){
                cout<<"there is no "<<name2<<endl;
                continue;
            }
            if(itres!=ms.end()){
                cout<<"name "<<nres<<" already been used"<<endl;
                continue;
            }
            Matrix mres=(it1->second)-(it2->second);
            if(!mres){
                cout<<"cannot calculate "<<name1<<" - "<<name2<<endl;
                continue;
            }
            ms[nres]=mres;
            cout<<"calculation result:"<<nres<<endl<<mres<<"---------------------------------"<<endl;


        }
        else if(cmd=="*"){
            string name1,name2,nres;
            cin>>name1>>name2>>nres;
            auto it1=ms.find(name1),it2=ms.find(name2),itres=ms.find(nres);
            if(it1==ms.end()){
                cout<<"there is no "<<name1<<endl;
                continue;
            }
            if(it2==ms.end()){
                cout<<"there is no "<<name2<<endl;
                continue;
            }
            if(itres!=ms.end()){
                cout<<"name "<<nres<<" already been used"<<endl;
                continue;
            }
            Matrix mres=(it1->second)*(it2->second);
            if(!mres){
                cout<<"cannot calculate "<<name1<<" * "<<name2<<endl;
                continue;
            }
            ms[nres]=mres;
            cout<<"calculation result:"<<nres<<endl<<mres<<"---------------------------------"<<endl;


        }
        else if(cmd=="*val"){
            string name1,nres;
            double d;
            cin>>name1>>d>>nres;
            auto it1=ms.find(name1),itres=ms.find(nres);
            if(it1==ms.end()){
                cout<<"there is no "<<name1<<endl;
                continue;
            }
            if(itres!=ms.end()){
                cout<<"name "<<nres<<" already been used"<<endl;
                continue;
            }
            Matrix mres=(it1->second)*d;
            if(!mres){
                cout<<"cannot calculate "<<name1<<" * "<<d<<endl;
                continue;
            }
            ms[nres]=mres;
            cout<<"calculation result:"<<nres<<endl<<mres<<"---------------------------------"<<endl;

        }
        else if(cmd=="det"){
            string name;
            cin>>name;
            auto it=ms.find(name);
            if(it==ms.end()){
                cout<<"no such name"<<endl;
                continue;
            }
            cout<<"det("<<name<<") is "<<(it->second).determinant()<<endl;
        }
        else if(cmd=="inv"){
             string name1,nres;
            cin>>name1>>nres;
            auto it1=ms.find(name1),itres=ms.find(nres);
            if(it1==ms.end()){
                cout<<"there is no "<<name1<<endl;
                continue;
            }
            if(itres!=ms.end()){
                cout<<"name "<<nres<<" already been used"<<endl;
                continue;
            }
            Matrix mres=it1->second.inverse();
            if(!mres){
                cout<<name1<<" is a singular matrix"<<endl;
                continue;
            }
            ms[nres]=mres;
            cout<<"calculation result:"<<nres<<endl<<mres<<"---------------------------------"<<endl;

        }
        else if(cmd=="rank"){
            string name;
            cin>>name;
            auto it=ms.find(name);
            if(it==ms.end()){
                cout<<"no such name"<<endl;
                continue;
            }
            cout<<"rank of "<<name<<" is "<<it->second.rank()<<endl;
        }
        else if(cmd=="tr"){
            string name;
            cin>>name;
            auto it=ms.find(name);
            if(it==ms.end()){
                cout<<"no such name"<<endl;
                continue;
            }
            cout<<"trace of "<<name<<" is "<<it->second.trace()<<endl;
        }
        else if(cmd=="trans"){
             string name1,nres;
            cin>>name1>>nres;
            auto it1=ms.find(name1),itres=ms.find(nres);
            if(it1==ms.end()){
                cout<<"there is no "<<name1<<endl;
                continue;
            }
            if(itres!=ms.end()){
                cout<<"name "<<nres<<" already been used"<<endl;
                continue;
            }
            Matrix mres=it1->second.transpose();
            ms[nres]=mres;
            cout<<"calculation result:"<<nres<<endl<<mres<<"---------------------------------"<<endl;

        }
    }

    return 0;
}
