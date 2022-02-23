#include <vector>
#include <iostream>
#include <set>

int segment_intersect (std::pair <int, int> s1, std::pair <int, int> s2)
{
    if      (s2.first  >= s1.first and s2.first <= s1.second)
        return 1;

    else if (s2.second >= s1.first and s2.second <= s1.second)
        return 1;

    else if (s1.first  >= s2.first and s1.first <= s2.second)
        return 1;

    else if (s1.second >= s2.first and s1.second <= s2.second)
        return 1;

    return 0;
}

class segment_tree
{
    std::vector <std::pair <int, int>> segments_;

    std::vector <int> numbers_;

    int size_ = 0;

    int l_border_ = 0, r_border_ = 0;

    segment_tree *left_ = nullptr, *right_ = nullptr;

    public:

    segment_tree (int l_border, int r_border): l_border_ (l_border), r_border_ (r_border) {}

    ~segment_tree ()
    {
        delete left_;
        delete right_;
    }

    int push (std::pair <int, int> segment, int num)
    {
        int center = (l_border_ + r_border_) / 2;

        if (segment.second < center or segment.first >= center)
        {
            if (left_ == nullptr and right_ == nullptr)
            {
                segment_tree* left  = new segment_tree (l_border_, center);
                segment_tree* right = new segment_tree (center, r_border_);

                left_  = left;
                right_ = right;
            }

            if (segment.second < center)
                left_->push (segment, num);

            else if (segment.first >= center)
                right_->push (segment, num);
        }

        else
        {
            segments_.push_back (segment);
            numbers_.push_back  (num);
            ++size_;
        }

        return 0;
    }

    int solution (std::set <int> &res) const
    {
        for (int i = 0; i < size_; ++i)
        {
            for (int j = 0; j < size_; ++j)
                if (i != j and res.find (i) == res.end() and segment_intersect (segments_[i], segments_[j]) == 1)
                {
                    res.insert (numbers_[i]);
                    res.insert (numbers_[j]);
                    break;
                }

            if (res.find (i) == res.end ())
            {
                if (left_ != nullptr and right_ != nullptr)
                {
                    left_->step_solution  (segments_[i], numbers_[i], res);
                    right_->step_solution (segments_[i], numbers_[i], res);
                }
            }
        }

        if (left_ != nullptr and right_ != nullptr)
        {
            left_->solution (res);
            right_->solution (res);
        }

        return 0;
    }

    int step_solution (std::pair <int, int> segment, int num,  std::set <int> &res) const
    {
        for (int i = 0; i < size_; ++i)
            if (segment_intersect (segment, segments_[i]) == 1)
            {
                res.insert (num);
                res.insert (numbers_[i]);
            }

        if (left_ != nullptr and right_ != nullptr)
        {
            left_->step_solution  (segment, num, res);
            right_->step_solution (segment, num, res);
        }

        return 0;
    }

    void print () const
    {
        std::cout << l_border_ << " " << r_border_ << "{\n";

        for (int i = 0; i < size_; ++i)
            std::cout << numbers_[i] << " ";

        std::cout << "\n";

        if (left_ != nullptr and right_ != nullptr)
        {
            left_->print ();
            right_->print ();
        }

        std::cout << "}\n";
    }
};

int main ()
{
    std::vector <std::pair <int, int>> segmnents = {};

    int size, x, y;

    int xmin = 0, ymax = 0;

    int key = 1;

    std::cin >> size;

    for (int i = 0; i < size; ++i)
    {
        std::cin >> x >> y;

        if (key)
        {
            xmin = x;
            ymax = y;
            key = 0;
        }

        if (xmin > x)
            xmin = x;

        if (ymax < y)
            ymax = y;

        segmnents.push_back (std::pair <int, int> {x ,y});
    }

    std::set <int> res = {};

    segment_tree *tree = new segment_tree (xmin - 1, ymax + 1);

    for (int i = 0; i < size; ++i)
        tree->push (segmnents[i], i);

    // tree->print();

    tree->solution (res);

    std::cout << size - res.size() << std::endl;

    delete tree;
}