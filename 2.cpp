#include <iostream>
#include <string>

// 定义统一的办证流程类
class DocumentProcess {
public:
    // 统一的办理流程接口
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
    std::string document_id;
};

// 身份证办理流程
class IDCardProcess : public DocumentProcess {
protected:
    void prepare(const std::string& id) override {document_id = id;}

    void handle(const std::string& id) override {std::cout << "处理身份证申请：" << id << std::endl;}

    void complete(const std::string& id) override {std::cout << "完成身份证办理：" << id << std::endl;}
};

// 护照办理流程
class PassportProcess : public DocumentProcess {
protected:
    void prepare(const std::string& id) override {document_id = id;}
    void handle(const std::string& id) override {std::cout << "处理护照申请：" << id << std::endl;}
    void complete(const std::string& id) override {std::cout << "完成护照办理：" << id << std::endl;}
};

// 通过多态方式进行调用
void start_process(DocumentProcess& process, const std::string& id) {
    process.go(id);
}

int main() {
    IDCardProcess id_card_process;
    PassportProcess passport_process;

    start_process(id_card_process, "123456789");
    start_process(passport_process, "987654321");

    return 0;
}
