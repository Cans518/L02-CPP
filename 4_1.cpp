#include <iostream>
#include <string>
#include <vector>
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
    // 纯虚函数，子类必须实现
    virtual void prepare(const std::string& document_id) = 0;
    virtual void handle(const std::string& document_id) = 0;
    virtual void complete(const std::string& document_id) = 0;
};

// 身份证办理流程的实现类
class IDCardProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {
        std::cout << "准备身份证办理材料：" << document_id << std::endl;
    }
    
    void handle(const std::string& document_id) override {
        std::cout << "处理身份证申请：" << document_id << std::endl;
    }
    
    void complete(const std::string& document_id) override {
        std::cout << "完成身份证办理：" << document_id << std::endl;
    }
};

// 护照办理流程的实现类
class PassportProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {
        std::cout << "准备护照办理材料：" << document_id << std::endl;
    }
    
    void handle(const std::string& document_id) override {
        std::cout << "处理护照申请：" << document_id << std::endl;
    }
    
    void complete(const std::string& document_id) override {
        std::cout << "完成护照办理：" << document_id << std::endl;
    }
};

// 结婚证办理流程的实现类
class MarriageCertProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {
        std::cout << "准备结婚证办理材料：" << document_id << std::endl;
    }
    
    void handle(const std::string& document_id) override {
        std::cout << "处理结婚证申请：" << document_id << std::endl;
    }
    
    void complete(const std::string& document_id) override {
        std::cout << "完成结婚证办理：" << document_id << std::endl;
    }
};

// 泛型类，办理指南类，使用模板 T 代表不同的办理流程
template <typename T>
class BanzhengGuide {
public:
    BanzhengGuide(const std::string& title, const std::string& description, const std::string& document_id, std::shared_ptr<T> process = nullptr)
        : title_(title), description_(description), document_id_(document_id), process_(process) {}

    void set_process(std::shared_ptr<T> process) {
        process_ = process;
    }

    void apply() {
        if (process_) {
            // 显示通用信息
            std::cout << "\n=== " << title_ << " ===" << std::endl;
            std::cout << "说明：" << description_ << std::endl;
            // 执行具体的办理流程
            process_->go(document_id_);
        } else {
            std::cout << "未设置办理流程" << std::endl;
        }
    }

    // 其他通用的属性和方法
    const std::string& title() const { return title_; }
    const std::string& description() const { return description_; }
    const std::string& document_id() const { return document_id_; }

protected:
    std::string title_;
    std::string description_;
    std::string document_id_;
    std::shared_ptr<T> process_;
};

// 主函数，演示如何使用这些类
int main() {
    // 创建办理流程实例
    std::shared_ptr<Process> id_card_process = std::make_shared<IDCardProcess>();
    std::shared_ptr<Process> passport_process = std::make_shared<PassportProcess>();
    std::shared_ptr<Process> marriage_cert_process = std::make_shared<MarriageCertProcess>();

    // 创建通用的办事指南实例
    BanzhengGuide<Process> id_card_guide("身份证办理指南", "办理身份证所需材料和流程说明", "ID20240101", id_card_process);
    BanzhengGuide<Process> passport_guide("护照办理指南", "办理护照所需材料和流程说明", "PP20240101", passport_process);
    BanzhengGuide<Process> marriage_cert_guide("结婚证办理指南", "办理结婚证所需材料和流程说明", "MC20240101", marriage_cert_process);

    // 模拟办理流程
    id_card_guide.apply();
    passport_guide.apply();
    marriage_cert_guide.apply();

    return 0;
}