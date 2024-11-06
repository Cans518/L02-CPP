/*
* 第三个题目主要就是使用模板方法对抽象类再次进行封装
*
*/

#include <iostream>
#include <string>
#include <memory>

// 抽象基类：办理流程的基础类
class Process {
protected:
    std::string document_id;
    // 虚函数：办理流程的步骤
    virtual void prepare(const std::string& document_id) = 0;
    virtual void handle(const std::string& document_id) = 0;
    virtual void complete(const std::string& document_id) = 0;

public:
    // 模板方法：办理流程的执行
    void go(const std::string& document_id) {
        prepare(document_id);
        handle(document_id);
        complete(document_id);
    }

    virtual ~Process() = default;
};

// 身份证办理流程的具体实现
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

// 护照办理流程的具体实现
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

// 模板类：泛型的办理指南
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

    // 设置办理流程
    void setProcess(std::shared_ptr<T> p) {
        process = p;
    }

    // 执行办理流程
    void apply() const {
        if (process) {
            process->go(document_id);
        } else {
            std::cout << "未设置办理流程" << std::endl;
        }
    }

    // 获取标题
    const std::string& getTitle() const {
        return title;
    }

    // 获取描述
    const std::string& getDescription() const {
        return description;
    }

    // 获取文档 ID
    const std::string& getDocumentId() const {
        return document_id;
    }
};

// 主函数：模拟流程
int main() {
    // 创建办理流程实例
    std::shared_ptr<IDCardProcess> id_card_process = std::make_shared<IDCardProcess>();
    std::shared_ptr<PassportProcess> passport_process = std::make_shared<PassportProcess>();

    // 创建办事指南实例
    BanzhengGuide<IDCardProcess> id_card_guide(
        "身份证办理指南",
        "办理身份证所需材料和流程说明",
        "ID20240101",
        id_card_process
    );

    BanzhengGuide<PassportProcess> passport_guide(
        "护照办理指南",
        "办理护照所需材料和流程说明",
        "PP20240101",
        passport_process
    );

    // 模拟办理流程
    std::cout << "=== 开始办理身份证 ===" << std::endl;
    id_card_guide.apply();

    std::cout << "\n=== 开始办理护照 ===" << std::endl;
    passport_guide.apply();

    return 0;
}
