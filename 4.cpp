#include <iostream>
#include <string>
#include <memory>

// 抽象基类，表示办理流程
class Process {
public:
    virtual ~Process() = default;
    
    // 模板方法，定义办理流程的顺序
    void go(const std::string& document_id) {
        prepare(document_id);
        handle(document_id);
        complete(document_id);
    }

protected:
    virtual void prepare(const std::string& document_id) = 0;
    virtual void handle(const std::string& document_id) = 0;
    virtual void complete(const std::string& document_id) = 0;
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

// 结婚证办理流程
class MarriageCertProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {std::cout << "准备结婚证材料：" << document_id << std::endl;}
    void handle(const std::string& document_id) override {std::cout << "处理结婚证申请：" << document_id << std::endl;}
    void complete(const std::string& document_id) override { std::cout << "完成结婚证办理：" << document_id << std::endl;}
};

// 办理指南类，使用模板 T 代表不同的办理流程
template <typename T>
class BanzhengGuide {
public:
    BanzhengGuide(std::string title, std::string description, std::string document_id, std::shared_ptr<T> process = nullptr)
        : title_(std::move(title)), description_(std::move(description)), document_id_(std::move(document_id)), process_(std::move(process)) {}

    void apply() const {
        if (process_) {
            std::cout << "\n=== " << title_ << " ===\n" << description_ << std::endl;
            process_->go(document_id_);
        } else {
            std::cout << "未设置办理流程" << std::endl;
        }
    }

private:
    std::string title_;
    std::string description_;
    std::string document_id_;
    std::shared_ptr<T> process_;
};

// 主函数
int main() {
    auto id_card_process = std::make_shared<IDCardProcess>();
    auto passport_process = std::make_shared<PassportProcess>();
    auto marriage_cert_process = std::make_shared<MarriageCertProcess>();

    BanzhengGuide<Process> id_card_guide("身份证办理指南", "身份证材料和流程", "ID20240101", id_card_process);
    BanzhengGuide<Process> passport_guide("护照办理指南", "护照材料和流程", "PP20240101", passport_process);
    BanzhengGuide<Process> marriage_cert_guide("结婚证办理指南", "结婚证材料和流程", "MC20240101", marriage_cert_process);

    id_card_guide.apply();
    passport_guide.apply();
    marriage_cert_guide.apply();

    return 0;
}