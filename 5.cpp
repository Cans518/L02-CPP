#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

// 抽象基类，表示办理流程
class Process {
public:
    virtual ~Process() = default;

    virtual void go(const std::string& document_id) {
        prepare(document_id);
        handle(document_id);
        complete(document_id);
    }

protected:
    virtual void prepare(const std::string& document_id) = 0;
    virtual void handle(const std::string& document_id) = 0;
    virtual void complete(const std::string& document_id) = 0;
};

// 身份证办理流程类
class IDCardProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {
        std::cout << "身份证: " << document_id << " - 准备材料" << std::endl;
    }

    void handle(const std::string& document_id) override {
        std::cout << "身份证: " << document_id << " - 处理中" << std::endl;
    }

    void complete(const std::string& document_id) override {
        std::cout << "身份证: " << document_id << " - 办理完成" << std::endl;
    }
};

// 护照办理流程类
class PassportProcess : public Process {
protected:
    void prepare(const std::string& document_id) override {
        std::cout << "护照: " << document_id << " - 准备材料" << std::endl;
    }

    void handle(const std::string& document_id) override {
        std::cout << "护照: " << document_id << " - 处理中" << std::endl;
    }

    void complete(const std::string& document_id) override {
        std::cout << "护照: " << document_id << " - 办理完成" << std::endl;
    }
};

// 泛型办理指南类
template <typename T>
class Guide {
public:
    Guide(std::string title, std::string description, std::string id, std::shared_ptr<T> process = nullptr)
        : title_(std::move(title)), description_(std::move(description)), id_(std::move(id)), process_(std::move(process)) {}

    void set_process(std::shared_ptr<T> process) {
        process_ = std::move(process);
    }

    virtual void apply() {
        if (process_) {
            process_->go(id_);
        } else {
            std::cerr << "Error: 未设置办理流程" << std::endl;
        }
    }

protected:
    std::string title_, description_, id_;
    std::shared_ptr<T> process_;
};

// 办证指南类
class BanzhengGuide : public Guide<Process> {
public:
    using Guide::Guide;
};

// 旅游类
class Tourism {
public:
    virtual ~Tourism() = default;

    virtual void go(const std::string& tour_id) {
        prepare_tour(tour_id);
        conduct_tour(tour_id);
        complete_tour(tour_id);
    }

protected:
    virtual void prepare_tour(const std::string& tour_id) = 0;
    virtual void conduct_tour(const std::string& tour_id) = 0;
    virtual void complete_tour(const std::string& tour_id) = 0;
};

// 北京旅游类
class BeijingTourism : public Tourism {
public:
    BeijingTourism() 
        : attractions_{"长城", "故宫", "颐和园"}, 
          duration_("3天2晚"), 
          transportation_{"大巴", "地铁"} {}

protected:
    void prepare_tour(const std::string& tour_id) override {
        std::cout << "旅游: " << tour_id << " - 行程天数: " << duration_ << std::endl;
        std::cout << "- 交通: " << join(transportation_) << std::endl;
    }

    void conduct_tour(const std::string& tour_id) override {
        std::cout << "旅游: " << tour_id << " - 景点: " << join(attractions_) << std::endl;
    }

    void complete_tour(const std::string& tour_id) override {
        std::cout << "旅游: " << tour_id << " - 结束" << std::endl;
    }

private:
    std::vector<std::string> attractions_, transportation_;
    std::string duration_;

    std::string join(const std::vector<std::string>& vec) const {
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << vec[i];
        }
        return oss.str();
    }
};

// 旅游指南类
class TourismGuide : public Guide<Tourism> {
public:
    TourismGuide(std::string title, std::string description, std::string tour_id, std::shared_ptr<Tourism> tourism = nullptr)
        : Guide(std::move(title), std::move(description), std::move(tour_id), std::move(tourism)),
          price_("2000元/人"), min_participants_(5), max_participants_(20), 
          meeting_point_("北京首都国际机场"), meeting_time_("上午9:00"),
          requirements_{"步行鞋", "防晒用品", "雨具", "身份证"} {}

    void show_tour_info() const {
        std::cout << "\n=== " << title_ << " ===" << std::endl;
        std::cout << "价格: " << price_ << ", 集合地点: " << meeting_point_ << ", 时间: " << meeting_time_ << std::endl;
        std::cout << "人数: " << min_participants_ << "-" << max_participants_ << "人" << std::endl;
        std::cout << "携带物品: " << join(requirements_) << std::endl;
    }

    void apply() override {
        show_tour_info();
        Guide::apply();
    }

private:
    std::string price_, meeting_point_, meeting_time_;
    int min_participants_, max_participants_;
    std::vector<std::string> requirements_;

    std::string join(const std::vector<std::string>& vec) const {
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << vec[i];
        }
        return oss.str();
    }
};

// 主函数
int main() {
    try {
        auto id_card_process = std::make_shared<IDCardProcess>();
        BanzhengGuide id_guide("身份证办理", "详细流程", "ID123456", id_card_process);
        id_guide.apply();

        auto passport_process = std::make_shared<PassportProcess>();
        BanzhengGuide passport_guide("护照办理", "详细流程", "PASSPORT78910", passport_process);
        passport_guide.apply();

        auto beijing_tour = std::make_shared<BeijingTourism>();
        TourismGuide beijing_guide("北京精华三日游", "打卡知名景点", "BJ20240101", beijing_tour);
        beijing_guide.apply();

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}