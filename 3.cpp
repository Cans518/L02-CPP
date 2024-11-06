#include <iostream>
#include <string>
#include <memory>

// 抽象基类：办理流程
class Process {
protected:
    virtual void prepare(const std::string& document_id) = 0;
    virtual void handle(const std::string& document_id) = 0;
    virtual void complete(const std::string& document_id) = 0;

public:
    void go(const std::string& document_id) {
        prepare(document_id);
        handle(document_id);
        complete(document_id);
    }

    virtual ~Process() = default;
};

// 身份证办理流程
class IDCardProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {std::cout << "准备身份证材料：" << document_id << std::endl;}

    void handle(const std::string& document_id) override {std::cout << "处理身份证申请：" << document_id << std::endl;}

    void complete(const std::string& document_id) override {std::cout << "完成身份证办理：" << document_id << std::endl;}
};

// 护照办理流程
class PassportProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {std::cout << "准备护照材料：" << document_id << std::endl;}

    void handle(const std::string& document_id) override {std::cout << "处理护照申请：" << document_id << std::endl;}

    void complete(const std::string& document_id) override {std::cout << "完成护照办理：" << document_id << std::endl;}
};

// 办理指南模板类
template <typename T>
class BanzhengGuide {
private:
    std::string title;
    std::string description;
    std::string document_id;
    std::shared_ptr<T> process;

public:
    BanzhengGuide(const std::string& title, const std::string& description, const std::string& document_id, std::shared_ptr<T> process = nullptr)
        : title(title), description(description), document_id(document_id), process(process) {}

    void apply() const {
        if (process) {
            process->go(document_id);
        } else {
            std::cout << "未设置办理流程" << std::endl;
        }
    }
};

// 主函数
int main() {
    auto id_card_process = std::make_shared<IDCardProcess>();
    auto passport_process = std::make_shared<PassportProcess>();

    BanzhengGuide<IDCardProcess> id_card_guide("身份证办理指南", "办理身份证所需材料和流程说明", "ID20240101", id_card_process);

    BanzhengGuide<PassportProcess> passport_guide("护照办理指南", "办理护照所需材料和流程说明", "PP20240101", passport_process);

    std::cout << "=== 办理身份证 ===" << std::endl;
    id_card_guide.apply();

    std::cout << "\n=== 办理护照 ===" << std::endl;
    passport_guide.apply();

    return 0;
}
