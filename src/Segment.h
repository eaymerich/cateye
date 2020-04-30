/*****************************************************************************
 * File: Segment.h
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#ifndef __SEGMENT_H__
#define __SEGMENT_H__

#include "Intersection.h"

#include <string>
#include <vector>

class Segment;

class SegmentList {
public:
    SegmentList() {
        ++count;
    }

    ~SegmentList() {
        ++count_des;
        acu_size += segments.size();
        if (segments.size() > max) {
            max = segments.size();
        }
    }

    void add(const Segment& segment) {
        segments.push_back(segment);
    }
    void add(const SegmentList& segmentList) {
        for (const auto& segment : segmentList.segments) {
            segments.push_back(segment);
        }
    }
    size_t size() const {
        return segments.size();
    };
    bool empty() const {
        return segments.empty();
    };
    Segment& operator[](std::size_t index) {
        return segments[index];
    };
    const Segment& operator[](std::size_t index) const {
        return segments[index];
    };

    // SegmentList-Segment operations
    SegmentList uunion(const Segment &other) const;
    SegmentList intersection(const Segment &other) const;
    SegmentList difference(const Segment &other) const;

    // SegmentList-Segment operations
    SegmentList uunion(const SegmentList &otherList) const;
    SegmentList intersection(const SegmentList &otherList) const;
    SegmentList difference(const SegmentList &otherList) const;

    std::string toString() const;

    static std::size_t count;
    static std::size_t count_des;
    static std::size_t acu_size;
    static std::size_t max;

protected:
    std::vector<Segment> segments;
};

class Segment {
public:
    Intersection a;
    Intersection b;

    Segment() = default;
    Segment(double a, double b);
    Segment(const Intersection &a, const Intersection &b);

    inline bool contains(const Intersection &intersection) const {
        return a <= intersection && intersection <= b;
    };

    inline bool overlaps(const Segment &other) const {
        //return !(a > other.b || b < other.a);
        return a <= other.b && b >= other.a;
    }

    inline bool operator<(const Segment& other) const {
        return a < other.a;
    };

    inline bool operator>(const Segment& other) const {
        return a > other.a;
    };

    SegmentList uunion(const Segment &other) const;
    SegmentList intersection(const Segment &other) const;
    SegmentList difference(const Segment &other) const;

    std::string toString() const;
};

#endif // __SEGMENT__
