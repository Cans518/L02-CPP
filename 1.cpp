/*
* 第一个题目主要是简单的方法，说明办证件的流程
*/

#include <iostream>
#include <string>

// 定义身份证办理流程类
class IDCardProcess{
    public:
        void start_process(std::string id){
            std::cout << "开始办理身份证" << std::endl;
            collect_id_info(id);
            handle_id_apply();
            check_material();
            confirm_id();
            finish_id_handle();

        }
    private:
        std::string docment_id;
        //收集身份证信息
        void collect_id_info(std::string id){
            std::cout << "收集身份证信息" << std::endl;
            docment_id = id;
        }
        // 处理身份证申请
        void handle_id_apply(){
            std::cout << "处理身份证申请" << std::endl;
        }
        // 完成身份证办理
        void finish_id_handle(){
            std::cout << "完成身份证办理" << std::endl;
        }
        // 额外步骤1：检查材料完整性
        void check_material(){
            std::cout << "额外步骤1：检查材料完整性" << std::endl;
        }
        // 额外步骤2：确认申请人身份
        void confirm_id(){
            std::cout << "额外步骤2：确认申请人身份" << std::endl;
        }
};

// 定义护照办理流程类
class PassportProcess{
    public:
        void start_process(std::string passport){
            std::cout << "开始办理护照" << std::endl;
            collect_passport_info(passport);
            handle_passport_apply();
            check_material();
            confirm_passport();
            finish_passport_handle();
        }
    private:
        std::string docment_passport;
        //收集护照信息
        void collect_passport_info(std::string passport){
            std::cout << "收集护照信息" << std::endl;
            docment_passport = passport;
        }
        // 处理护照申请
        void handle_passport_apply(){
            std::cout << "处理护照申请" << std::endl;
        }
        // 完成护照办理
        void finish_passport_handle(){
            std::cout << "完成护照办理" << std::endl;
        }
        // 额外步骤1：确认护照类型
        void check_material(){
            std::cout << "额外步骤1：确认护照类型" << std::endl;
        }
        // 额外步骤2：检查照片要求
        void confirm_passport(){
            std::cout << "额外步骤2：检查照片要求" << std::endl;
        }

};

int main(){
    
    IDCardProcess id_card_process;  // 创建身份证办理流程对象
    PassportProcess passport_process;  // 创建护照办理流程对象
    
    id_card_process.start_process("123456789");  // 调用身份证办理流程

    passport_process.start_process("987654321");  // 调用护照办理流程
    return 0;
}