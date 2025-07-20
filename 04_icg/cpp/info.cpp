#pragma once;
#include <string>

class Info {
    public:
        std::string line = "";
        int line_no = -1;

        Info* set_line(std::string line, int line_no, int gap = 0, int new_line = 0){
            if(this->line_no == -1)
                this->line_no = line_no;

            if(this->line_no < line_no)
                this->line_no = line_no;
        
            this->line += line;
        
            while(gap != 0){
                this->line += " ";
                gap--;
            }
        
            while(new_line != 0){
                this->line += "\n";
                new_line--;
            }
        
            return this;
        }
        
        Info* set_line(Info &info, int gap = 0, int new_line = 0){
            if(this->line_no == -1)
                this->line_no = info.line_no;
            
            if(this->line_no < info.line_no)
                this->line_no = info.line_no;
        
        
            this->line += info.line;
            
            while(gap != 0){
                this->line += " ";
                gap--;
            }
        
            while(new_line != 0){
                this->line += "\n";
                new_line--;
            }
        
            return this;
        }
        
};

class Param{
    public:
        std::string type;
        std::string name = "const"; 
        bool is_array;
        int array_size = 1;
        bool is_func;
        std::string value;

        Param(){};

        Param(std::string name, bool is_array = false, bool is_func = false){
            this->name = name;
            this->is_array = is_array;
            this->is_func = is_func;
        }

        Param(std::string type, std::string name, bool is_array = false, bool is_func = false){
            this->type = type;
            this->name = name;
            this->is_array = is_array;
            this->is_func = is_func;
        }

        Param& operator=(const Param &p){
            this->type = p.type;
            this->name = p.name;
            this->is_array = p.is_array;
            this->is_func = p.is_func;
            this->value = p.value;

            return *this;
        }
};



// class Info {
//     public:
//         std::string line = "";
//         int line_no = -1;

//         Info* set_line(std::string line, int line_no, int gap = 0, int new_line = 0);

//         Info* set_line(Info &info, int gap = 0, int new_line = 0);
        
// };

// Info* Info::set_line(std::string line, int line_no, int gap, int new_line){
//     if(this->line_no == -1)
//         this->line_no = line_no;

//     this->line += line;

//     while(gap != 0){
//         this->line += " ";
//         gap--;
//     }

//     while(new_line != 0){
//         this->line += "\n";
//         new_line--;
//     }

//     return this;
// }

// Info* Info::set_line(Info &info, int gap, int new_line){
//     if(this->line_no == -1)
//         this->line_no = info.line_no;

//     this->line += info.line;
    
//     while(gap != 0){
//         this->line += " ";
//         gap--;
//     }

//     while(new_line != 0){
//         this->line += "\n";
//         new_line--;
//     }

//     return this;
// }
