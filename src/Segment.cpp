/*****************************************************************************
 * File: Segment.cpp
 * Author: Edward Aymerich Sanchez
 * Year: 2020
*****************************************************************************/

#include <algorithm>
#include <sstream>
#include "Segment.h"

std::size_t SegmentList::count = 0;
std::size_t SegmentList::count_des = 0;
std::size_t SegmentList::acu_size = 0;
std::size_t SegmentList::max = 0;

Segment::Segment(double a, double b)
    : a{a}, b{b}
{}

Segment::Segment(const Intersection &a, const Intersection &b)
    : a{a}, b{b}
{}

SegmentList
Segment::uunion(const Segment &other) const
{
    SegmentList result;
    if (overlaps(other)) {
        // If segments overlap, the union is only one segment.
        auto t0 = std::min(a, other.a);
        auto t1 = std::max(b, other.b);
        result.add(Segment(t0, t1));
    } else {
        // If segments do not overlap, the union is two segments,
        // ordered by distance.
        auto s0 = std::min(*this, other);
        auto s1 = std::max(*this, other);
        result.add(s0);
        result.add(s1);
    }
    return result;
}

SegmentList
Segment::intersection(const Segment &other) const
{
    SegmentList result;
    if (overlaps(other)) {
        auto t0 = std::max(a, other.a);
        auto t1 = std::min(b, other.b);
        result.add(Segment(t0, t1));
    }
    return result;
}

SegmentList
Segment::difference(const Segment &other) const
{
    SegmentList result;

    if (overlaps(other)) {
        auto contains_a = contains(other.a);
        auto contains_b = contains(other.b);
        if (contains_a && contains_b) {
            // This segment will be cut in the middle.
            result.add(Segment(a, other.a));
            result.add(Segment(other.b, b));
        } else if (contains_a) {
            // This segment will be cut at the end.
            result.add(Segment(a, other.a));
        } else if (contains_b) {
            // This segment will be cut at the beggining.
            result.add(Segment(other.b, b));
        } 
    } else {
        // The other segment does not overlap this segment,
        // so there is no cut.
        result.add(*this);
    }

    return result;
}

std::string
Segment::toString() const
{
    std::stringstream ss;
    ss << '[' << a.getDistance() << ',' << b.getDistance() << ']';
    return ss.str();
}


std::string
SegmentList::toString() const
{
    std::stringstream ss;
    ss << "[ ";
    for (const auto& seg : segments) {
        ss << seg.toString() << ' ';
    }
    ss << ']';
    return ss.str();
}

SegmentList
SegmentList::uunion(const Segment &other) const
{
    SegmentList result;
    bool other_added = false;

    size_t i = 0;
    while (i < segments.size()) {
        const auto& current = segments[i];
        if (other_added || current.b < other.a) {
            // Other segment is already added, so just add current, or
            // current segment should be added before other.
            result.add(current);
            ++i;
        } else if (other.b < current.a) {
            // Other segment should be added before current.
            result.add(other);
            other_added = true;
        } else {
            // Current and other segments overlap. Union must have only one segment.
            auto united = current.uunion(other)[0];
            ++i;

            // Check if next segments overlaps with united segment.
            while (i < segments.size() && segments[i].a < united.b) {
                united = united.uunion(segments[i])[0];
                ++i;
            }

            result.add(united);
            other_added = true;
        }
    }

    if (!other_added) {
        result.add(other);
    }

    return result;
}

SegmentList
SegmentList::intersection(const Segment &other) const
{
    SegmentList result;

    for (const auto& current : segments) {
        if (current.overlaps(other)) {
            result.add(current.intersection(other)[0]);
        }
    }

    return result;
}

SegmentList
SegmentList::difference(const Segment &other) const
{
    SegmentList result;

    for (const auto& current : segments) {
        if (current.overlaps(other)) {
            result.add(current.difference(other)[0]);
        } else {
            result.add(current);
        }
    }

    return result;
}

SegmentList
SegmentList::uunion(const SegmentList &otherList) const
{
    SegmentList result;

    size_t i = 0;
    size_t j = 0;
    while (i < segments.size() && j < otherList.segments.size()) {
        const auto& current = segments[i];
        const auto& other   = otherList.segments[j];
        if (current.b < other.a) {
            // Current segment should be added before other.
            result.add(current);
            ++i;
        } else if (other.b < current.a) {
            // Other segment should be added before current.
            result.add(other);
            ++j;
        } else {
            // Current and other segments overlap. Union must have only one segment.
            auto united = current.uunion(other)[0];
            ++i;
            ++j;

            // Check if next segments overlaps with united segment.
            while (i < segments.size() && segments[i].a < united.b) {
                united = united.uunion(segments[i])[0];
                ++i;
            }

            // Check if next segment in otherList overlaps with united segment.
            while (j < otherList.segments.size() && otherList.segments[j].a < united.b) {
                united = united.uunion(otherList.segments[j])[0];
                ++j;
            }

            result.add(united);
        }
    }

    while (i < segments.size()) {
        result.add(segments[i]);
        ++i;
    }

    while (j < otherList.segments.size()) {
        result.add(otherList.segments[j]);
        ++j;
    }

    return result;
}

SegmentList
SegmentList::intersection(const SegmentList &otherList) const
{
    SegmentList result;

    size_t i = 0;
    size_t j = 0;
    while (i < segments.size() && j < otherList.segments.size()) {
        const auto& current = segments[i];
        const auto& other   = otherList.segments[j];
        if (current.b < other.a) {
            // Current segment should be added before other.
            ++i;
        } else if (other.b < current.a) {
            // Other segment should be added before current.
            ++j;
        } else {
            // Current and other segments overlap. Intersection must have only one segment.
            auto intersected = current.intersection(other)[0];

            // Discard only first segment to end
            if (current.b < other.b) {
                ++i;
            } else {
                ++j;
            }

            result.add(intersected);
        }
    }

    return result;
}

SegmentList
SegmentList::difference(const SegmentList &otherList) const
{
    SegmentList result;

    size_t i = 0;
    size_t j = 0;
    Segment current;
    if (i < segments.size()) {
        current = segments[i];
    }

    while (i < segments.size() && j < otherList.segments.size()) {
        const auto &other = otherList.segments[j];

        if (current.b <= other.a) {
            // Current segment should be added before other.
            result.add(current);
            ++i;
            if (i < segments.size()) {
                current = segments[i];
            }
        } else if (other.b < current.a) {
            // Other segment should be skipped, as it is no longer relevant
            ++j;
        } else {
            // Current and other segments overlap.
            auto diff = current.difference(other);

            switch (diff.size()) {
            case 2:
                // *-------* -
                //    *--*   =
                // *--*  *-*
                // Add fist result, keep second result as current
                // to compare it against other segments in otherList.
                // Advance other segment.
                result.add(diff[0]);
                current = diff[1];
                ++j;
                break;
            case 1:
                if (current.b < other.b) {
                    // *-------*  -
                    //      *---* =
                    // *----*
                    // Add result and advance current segment.
                    result.add(diff[0]);
                    ++i;
                    if (i < segments.size()) {
                        current = segments[i];
                    }
                } else {
                    //  *-------* -
                    // *---*      =
                    //     *----*
                    // Keep result as current to compare with other segments
                    // in otherList. Advance other segment.
                    current = diff[0];
                    ++j;
                }
                break;
            case 0:
                // There is no result. Advance current segment.
                ++i;
                if (i < segments.size()) {
                    current = segments[i];
                }
                break;
            }
        }
    }

    if (i < segments.size()) {
        ++i;
        result.add(current);
        while (i < segments.size()){
            result.add(segments[i]);
            ++i;
        }
    }

    return result;
}
