#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 抽象基类，表示办理流程
class Process {
public:
    virtual ~Process() = default;

    // go 方法，处理整个流程，子类可以重写，但通常不需要重写
    virtual void go(const std::string& document_id) {
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

// 身份证办理流程类
class IDCardProcess : public Process {
protected:
    // 重写父类的纯虚函数
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

// 护照办理流程类
class PassportProcess : public Process {
protected:
    // 重写父类的纯虚函数
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

// 泛型办理指南类
template <typename T>
class BanzhengGuideUniverse {
public:
    BanzhengGuideUniverse(const std::string& title, const std::string& description, const std::string& document_id, std::shared_ptr<T> process = nullptr)
        : title_(title), description_(description), document_id_(document_id), process_(process) {}

    // 设置办理流程
    void set_process(std::shared_ptr<T> process) {
        process_ = process;
    }

    // 开始办理流程
    virtual void apply() {
        if (process_) {
            process_->go(document_id_);
        } else {
            std::cerr << "Error: 未设置办理流程或流程不支持go方法" << std::endl;
        }
    }

protected:
    // 受保护的成员变量，子类可以访问
    std::string title_;
    std::string description_;
    std::string document_id_;
    std::shared_ptr<T> process_;
};

// 办证指南类，继承自泛型办理指南类
class BanzhengGuide : public BanzhengGuideUniverse<Process> {
public:
    using BanzhengGuideUniverse::BanzhengGuideUniverse;
};

// 旅游类
class Tourism {
public:
    virtual ~Tourism() = default;

    // go 方法，处理旅游流程
    virtual void go(const std::string& tour_id) {
        prepare_tour(tour_id);
        conduct_tour(tour_id);
        complete_tour(tour_id);
    }

protected:
    // 纯虚函数，子类必须实现
    virtual void prepare_tour(const std::string& tour_id) = 0;
    virtual void conduct_tour(const std::string& tour_id) = 0;
    virtual void complete_tour(const std::string& tour_id) = 0;
};

// 北京旅游类，继承自旅游类
class BeijingTourism : public Tourism {
public:
    BeijingTourism() {
        local_specialties_ = {"烤鸭", "炸酱面"};
        shopping_spots_ = {"王府井", "秀水街"};
        evening_activities_ = {"观看功夫表演", "品尝夜市小吃"};
    }

protected:
    // 重写父类的纯虚函数
    void prepare_tour(const std::string& tour_id) override {
        std::cout << "准备旅游行程：" << tour_id << std::endl;
        std::cout << "- 行程天数：3天2晚" << std::endl;
        std::cout << "- 交通方式：大巴, 地铁" << std::endl;
        std::cout << "特色安排：" << std::endl;
        std::cout << "- 美食推荐：" << join(local_specialties_, ", ") << std::endl;
        std::cout << "- 购物地点：" << join(shopping_spots_, ", ") << std::endl;
    }

    void conduct_tour(const std::string& tour_id) override {
        std::cout << "开始旅游：" << tour_id << std::endl;
        std::cout << "景点安排：" << std::endl;
        for (const auto& attraction : attractions_) {
            std::cout << "- " << attraction << std::endl;
        }
        std::cout << "夜间活动：" << std::endl;
        for (const auto& activity : evening_activities_) {
            std::cout << "- " << activity << std::endl;
        }
    }

    void complete_tour(const std::string& tour_id) override {
        std::cout << "完成旅游：" << tour_id << std::endl;
        std::cout << "- 收集游客反馈" << std::endl;
        std::cout << "- 办理退房手续" << std::endl;
    }

private:
    // 私有成员变量，只能在类内部访问
    std::vector<std::string> local_specialties_;
    std::vector<std::string> shopping_spots_;
    std::vector<std::string> evening_activities_;

    // 辅助函数：将字符串数组连接成一个字符串
    std::string join(const std::vector<std::string>& vec, const std::string& delimiter) const {
        std::string result;
        for (size_t i = 0; i < vec.size(); ++i) {
            result += vec[i];
            if (i < vec.size() - 1) {
                result += delimiter;
            }
        }
        return result;
    }

protected:
    // 受保护的成员变量，子类可以访问和修改
    std::vector<std::string> attractions_ = {"长城", "故宫", "颐和园"};
};

// 旅游指南类，继承自泛型办理指南类
class TourismGuide : public BanzhengGuideUniverse<Tourism> {
public:
    TourismGuide(const std::string& title, const std::string& description, const std::string& tour_id, std::shared_ptr<Tourism> tourism = nullptr)
        : BanzhengGuideUniverse(title, description, tour_id, tourism) {
        price_ = "2000元/人";
        min_participants_ = 5;
        max_participants_ = 20;
        meeting_point_ = "北京首都国际机场";
        meeting_time_ = "上午9:00";
        requirements_ = {"舒适的步行鞋", "防晒用品", "雨具", "身份证原件"};
    }

    // 显示旅游信息
    void show_tour_info() const {
        std::cout << "\n=== " << title_ << " ===" << std::endl;
        std::cout << "行程说明：" << description_ << std::endl;
        std::cout << "团号：" << document_id_ << std::endl;
        std::cout << "价格：" << price_ << std::endl;
        std::cout << "集合地点：" << meeting_point_ << std::endl;
        std::cout << "集合时间：" << meeting_time_ << std::endl;
        std::cout << "人数要求：" << min_participants_ << "-" << max_participants_ << "人" << std::endl;
        std::cout << "\n携带物品要求：" << std::endl;
        for (const auto& item : requirements_) {
            std::cout << "- " << item << std::endl;
        }
    }

    // 开始旅游流程
    void apply() override {
        show_tour_info();
        std::cout << "\n开始行程：" << std::endl;
        BanzhengGuideUniverse::apply();
    }

private:
    // 私有成员变量，只能在类内部访问
    std::string price_;
    int min_participants_;
    int max_participants_;
    std::string meeting_point_;
    std::string meeting_time_;
    std::vector<std::string> requirements_;
};

// 主函数
int main() {
    try {
        // 办证流程测试
        std::cout << "\n==== 办证流程测试 ====\n" << std::endl;

        // 创建身份证办理流程实例
        auto id_card_process = std::make_shared<IDCardProcess>();
        BanzhengGuide id_guide(
            "身份证办理",
            "办理身份证的详细流程",
            "ID123456",
            id_card_process
        );
        std::cout << "开始身份证办理流程：" << std::endl;
        id_guide.apply();  // 模拟身份证办理流程

        std::cout << "\n-------------------------\n" << std::endl;

        // 创建护照办理流程实例
        auto passport_process = std::make_shared<PassportProcess>();
        BanzhengGuide passport_guide(
            "护照办理",
            "办理护照的详细流程",
            "PASSPORT78910",
            passport_process
        );
        std::cout << "开始护照办理流程：" << std::endl;
        passport_guide.apply();  // 模拟护照办理流程

        std::cout << "\n==== 旅游流程测试 ====\n" << std::endl;

        // 旅游流程测试
        auto beijing_tour = std::make_shared<BeijingTourism>();
        TourismGuide beijing_guide(
            "北京精华三日游",
            "打卡北京知名景点，体验地道美食文化",
            "BJ20240101",
            beijing_tour
        );
        beijing_guide.apply();  // 模拟旅游流程

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
