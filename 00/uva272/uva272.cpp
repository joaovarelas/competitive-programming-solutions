#include <iostream>
#include <string>

int main(){
    
    std::string s;
    
    bool flag = false;

    /*
    while(std::getline(std::cin, s)){
        
        if(first)
            first = false;
        else
            std::cout << std::endl;
             
        for(std::string::iterator it = s.begin(); it != s.end(); ++it){
            const char c = *it;
            if(c == '"'){
                if(!flag){
                    std::cout << "``";
                }else{
                    std::cout << "''";
                }
                flag = !flag;
            }else{
                std::cout << std::string(1, c);
            }
            }
        
            }
    */

 
    char c;


    while( (c = getchar()) != EOF ){
      
    if(c == '"'){
        if(!flag){
            std::cout << "``";
        }else{
            std::cout << "''";
        }
        flag = !flag;
    }else{
        std::cout << std::string(1, c);
    }
        
}
       
    
    return 0;
}
