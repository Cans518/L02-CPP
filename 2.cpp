/*
*   第二个题目引入抽象类概念，用一个流程类来处理各种证件的办理流程
*  - 定义抽象类
*  - 定义抽象方法
*  - 定义具体类
*  - 简单指针实现多态
*/

#include <iostream>
#include <string>

// 定义统一的办证流程类
class DocumentProcess {
public:
    // 定义统一的办理流程方法接口go
    void go(const std::string& id) {
        prepare(id);
        handle(id);
        complete(id);
    }

    virtual ~DocumentProcess() {}

protected:
    virtual void prepare(const std::string& id) = 0;
    virtual void handle(const std::string& id) = 0;
    virtual void complete(const std::string& id) = 0;
};

// 定义身份证办理流程类
class IDCardProcess : public DocumentProcess {
public:
    void prepare(const std::string& id) override {
        std::cout << "收集身份证信息" << std::endl;
        document_id = id;
    }

    void handle(const std::string& id) override {
        std::cout << "处理身份证 id 为：" << id << " 的申请" << std::endl;
    }

    void complete(const std::string& id) override {
        std::cout << "完成身份证 id 为：" << id << " 的办理" << std::endl;
    }

private:
    std::string document_id;
};

// 定义护照办理流程类
class PassportProcess : public DocumentProcess {
public:
    void prepare(const std::string& id) override {
        std::cout << "收集护照信息" << std::endl;
        document_id = id;
    }

    void handle(const std::string& id) override {
        std::cout << "处理护照 id 为：" << id << " 的申请" << std::endl;
    }

    void complete(const std::string& id) override {
        std::cout << "完成护照 id 为：" << id << " 的办理" << std::endl;
    }

private:
    std::string document_id;
};

// 通过多态方式进行调用
void start_process(DocumentProcess& process, const std::string& id) {
    std::cout << "开始办理流程：" << std::endl;
    process.go(id);
}

int main() {
    IDCardProcess id_card_process;
    PassportProcess passport_process;

    // 通过多态进行调用
    start_process(id_card_process, "123456789");
    start_process(passport_process, "987654321");

    return 0;
}
