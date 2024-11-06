#include <iostream>
#include <string>

// 身份证办理流程类
class IDCardProcess {
public:
    void start_process(const std::string& id) {
        std::cout <<"办理身份证流程开始" << std::endl;
        collect_id_info(id);
        handle_id_apply();
        check_material();
        confirm_id();
        finish_id_handle();
    }

private:
    void collect_id_info(const std::string& id) {std::cout << "收集身份证信息: " << id << std::endl;}      // 收集身份证信息
    
    void handle_id_apply() {std::cout << "处理身份证申请" << std::endl;}        // 处理身份证申请

    void check_material() {std::cout << "检查身份证材料" << std::endl;}         // 检查身份证材料

    void confirm_id() {std::cout << "确认身份证申请人身份" << std::endl;}       // 确认申请人身份

    void finish_id_handle() {std::cout << "身份证办理完成" << std::endl;}       // 完成身份证办理
};

// 护照办理流程类
class PassportProcess {
public:
    void start_process(const std::string& passport) {
        std::cout << "办理护照流程开始" << std::endl;
        collect_passport_info(passport);
        handle_passport_apply();
        check_material();
        confirm_passport();
        finish_passport_handle();
    }

private:
    
    void collect_passport_info(const std::string& passport) {std::cout << "收集护照信息: " << passport << std::endl;}  // 收集护照信息

    void handle_passport_apply() {std::cout << "处理护照申请" << std::endl;}     // 处理护照申请

    void check_material() {std::cout << "确认护照材料" << std::endl;}           // 确认护照材料

    void confirm_passport() {std::cout << "检查护照照片要求" << std::endl;}     // 检查照片要求
    
    void finish_passport_handle() {std::cout << "护照办理完成" << std::endl;}   // 完成护照办理
};

int main() {
    IDCardProcess id_card_process;  // 创建身份证办理流程对象
    PassportProcess passport_process;  // 创建护照办理流程对象

    id_card_process.start_process("123456789");  // 调用身份证办理流程
    passport_process.start_process("987654321");  // 调用护照办理流程

    return 0;
}