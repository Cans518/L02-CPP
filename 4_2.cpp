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
    BanzhengGuide(const std::string& title, const std::string& description, const std::string& document_id, 
                  const std::vector<std::string>& required_documents, const std::string& processing_time, 
                  const std::string& fee, const std::string& valid_period, std::shared_ptr<T> process = nullptr)
        : title_(title), description_(description), document_id_(document_id), 
          required_documents_(required_documents), processing_time_(processing_time), 
          fee_(fee), valid_period_(valid_period), process_(process) {}

    void set_process(std::shared_ptr<T> process) {
        process_ = process;
    }

    void apply() {
        std::cout << "\n=== " << title_ << " ===" << std::endl;
        std::cout << "说明：" << description_ << std::endl;
        check_documents();
        std::cout << "预计办理时间：" << processing_time_ << std::endl;
        std::cout << "办理费用：" << fee_ << std::endl;
        if (!valid_period_.empty()) {
            std::cout << "有效期：" << valid_period_ << std::endl;
        }
        if (process_) {
            process_->go(document_id_);
        } else {
            std::cout << "未设置办理流程" << std::endl;
        }
    }

protected:
    // 核对办理所需材料
    void check_documents() {
        std::cout << "核对所需材料：" << std::endl;
        for (const auto& doc : required_documents_) {
            std::cout << "- " << doc << std::endl;
        }
    }

    // 通用属性
    std::string title_;
    std::string description_;
    std::string document_id_;
    std::vector<std::string> required_documents_;
    std::string processing_time_;
    std::string fee_;
    std::string valid_period_;
    std::shared_ptr<T> process_;
};

// 身份证办理指南类
class IDCardGuide : public BanzhengGuide<Process> {
public:
    IDCardGuide(const std::string& title, const std::string& description, const std::string& document_id, std::shared_ptr<Process> process = nullptr)
        : BanzhengGuide(title, description, document_id, 
                        {"户口本", "居住证明", "照片", "临时身份证明（如有）", "原身份证（换证时需要）"}, 
                        "5-7个工作日", "20元", "20年", process) {}
};

// 护照办理指南类
class PassportGuide : public BanzhengGuide<Process> {
public:
    PassportGuide(const std::string& title, const std::string& description, const std::string& document_id, std::shared_ptr<Process> process = nullptr)
        : BanzhengGuide(title, description, document_id, 
                        {"身份证", "户口本", "照片", "申请表", "未成年人需监护人同意书"}, 
                        "10-15个工作日", "200元", "10年（成年人）/5年（未成年人）", process) {}
};

// 结婚证办理指南类
class MarriageCertGuide : public BanzhengGuide<Process> {
public:
    MarriageCertGuide(const std::string& title, const std::string& description, const std::string& document_id, std::shared_ptr<Process> process = nullptr)
        : BanzhengGuide(title, description, document_id, 
                        {"双方身份证", "双方户口本", "双方照片", "婚姻状况证明", "未婚声明书"}, 
                        "当场办理", "9元", "", process) {}  // 结婚证没有有效期，所以传空字符串
};

// 主函数，演示如何使用这些类
int main() {
    // 创建办理流程实例
    std::shared_ptr<Process> id_card_process = std::make_shared<IDCardProcess>();
    std::shared_ptr<Process> passport_process = std::make_shared<PassportProcess>();
    std::shared_ptr<Process> marriage_cert_process = std::make_shared<MarriageCertProcess>();

    // 创建办事指南实例
    IDCardGuide id_card_guide("身份证办理指南", "办理身份证所需材料和流程说明", "ID20240101", id_card_process);
    PassportGuide passport_guide("护照办理指南", "办理护照所需材料和流程说明", "PP20240101", passport_process);
    MarriageCertGuide marriage_cert_guide("结婚证办理指南", "办理结婚证所需材料和流程说明", "MC20240101", marriage_cert_process);

    // 模拟办理流程
    id_card_guide.apply();
    passport_guide.apply();
    marriage_cert_guide.apply();

    return 0;
}
