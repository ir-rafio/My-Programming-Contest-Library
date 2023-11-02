typedef long double Tf;
typedef long long Ti;
const Tf PI = acos(-1), EPS = 1e-9;
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x<0 ? -1 : 1);}

struct Point {
    Ti x, y;
    Point(Ti x = 0, Ti y = 0) : x(x), y(y) {}

    Point operator + (const Point& u) const { return Point(x + u.x, y + u.y); }
    Point operator - (const Point& u) const { return Point(x - u.x, y - u.y); }
    Point operator * (const long long u) const { return Point(x * u, y * u); }
    Point operator * (const Tf u) const { return Point(x * u, y * u); }
    Point operator / (const Tf u) const { return Point(x / u, y / u); }

    bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
    bool operator != (const Point& u) const { return !(*this == u); }
    bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0); }
    friend istream &operator >> (istream &is, Point &p) { return is >> p.x >> p.y; }
    friend ostream &operator << (ostream &os, const Point &p) { return os << p.x << " " << p.y; }
};

Ti dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
Ti cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
Tf length(Point a) { return sqrt(dot(a, a)); }
Ti sqLength(Point a) { return dot(a, a); }
Tf distance(Point a, Point b) {return length(a-b);}
Tf angle(Point u) { return atan2(u.y, u.x); }

// returns angle between oa, ob in (-PI, PI]
Tf angleBetween(Point a, Point b) {
    Tf ans = angle(b) - angle(a);
    return ans <= -PI ? ans + 2*PI : (ans > PI ? ans - 2*PI : ans);
}

// Rotate a ccw by rad radians
Point rotate(Point a, Tf rad) {
    static_assert(is_same<Tf, Ti>::value);
    return Point(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}

// rotate a ccw by angle th with cos(th) = co && sin(th) = si
Point rotatePrecise(Point a, Tf co, Tf si) {
    static_assert(is_same<Tf, Ti>::value);
    return Point(a.x * co - a.y * si, a.y * co + a.x * si);
}

Point rotate90(Point a) { return Point(-a.y, a.x); }

// scales vector a by s such that length of a becomes s
Point scale(Point a, Tf s) {
    static_assert(is_same<Tf, Ti>::value);
    return a / length(a) * s;
}

// returns an unit vector perpendicular to vector a
Point normal(Point a) {
    static_assert(is_same<Tf, Ti>::value);
    Tf l = length(a);
    return Point(-a.y / l, a.x / l);
}

// returns 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c) {
    return dcmp(cross(b - a, c - a));
}

///Use as sort(v.begin(), v.end(), polarComp(O, dir))
///Polar comparator around O starting at direction dir
struct polarComp {
    Point O, dir;
    polarComp(Point O = Point(0, 0), Point dir = Point(1, 0))
        : O(O), dir(dir) {}
    bool half(Point p) {
        return dcmp(cross(dir, p)) < 0 || (dcmp(cross(dir, p)) == 0 && dcmp(dot(dir, p)) > 0);
    }
    bool operator()(Point p, Point q) {
        return make_tuple(half(p-O), 0) < make_tuple(half(q-O), cross(p-O, q-O));
    }
};


struct Segment {
    Point a, b;
    Segment() {}
    Segment(Point aa, Point bb) : a(aa), b(bb) {}
};
typedef Segment Line;

struct Circle {
    Point o;
    Tf r;
    Circle(Point o = Point(0, 0), Tf r = 0) : o(o), r(r) {}

    // returns true if point p is in || on the circle
    bool contains(Point p) {
        return dcmp(sqLength(p - o) - r * r) <= 0;
    }

    // returns a point on the circle rad radians away from +X CCW
    Point point(Tf rad) {
        static_assert(is_same<Tf, Ti>::value);
        return Point(o.x + cos(rad) * r, o.y + sin(rad) * r);
    }

    // area of a circular sector with central angle rad
    Tf area(Tf rad = PI + PI) { return rad * r * r / 2; }

    // area of the circular sector cut by a chord with central angle alpha
    Tf sector(Tf alpha) { return r * r * 0.5 * (alpha - sin(alpha)); }
};

namespace Linear {
    // returns true if point p is on segment s
    bool onSegment(Point p, Segment s) {
        return dcmp(cross(s.a - p, s.b - p)) == 0 && dcmp(dot(s.a - p, s.b - p)) <= 0;
    }

    // returns true if segment p && q touch or intersect
    bool segmentsIntersect(Segment p, Segment q) {
        if(onSegment(p.a, q) || onSegment(p.b, q)) return true;
        if(onSegment(q.a, p) || onSegment(q.b, p)) return true;

        Ti c1 = cross(p.b - p.a, q.a - p.a);
        Ti c2 = cross(p.b - p.a, q.b - p.a);
        Ti c3 = cross(q.b - q.a, p.a - q.a);
        Ti c4 = cross(q.b - q.a, p.b - q.a);
        return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
    }

    bool linesParallel(Line p, Line q) {
        return dcmp(cross(p.b - p.a, q.b - q.a)) == 0;
    }

    // lines are represented as a ray from a point: (point, vector)
    // returns false if two lines (p, v) && (q, w) are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Point p, Point v, Point q, Point w, Point& o) {
        static_assert(is_same<Tf, Ti>::value);
        if(dcmp(cross(v, w)) == 0) return false;
        Point u = p - q;
        o = p + v * (cross(w,u)/cross(v,w));
        return true;
    }

    // returns false if two lines p && q are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Line p, Line q, Point& o) {
        return lineLineIntersection(p.a, p.b - p.a, q.a, q.b - q.a, o);
    }

    // returns the distance from point a to line l
    Tf distancePointLine(Point p, Line l) {
        return abs(cross(l.b - l.a, p - l.a) / length(l.b - l.a));
    }

    // returns the shortest distance from point a to segment s
    Tf distancePointSegment(Point p, Segment s) {
        if(s.a == s.b) return length(p - s.a);
        Point v1 = s.b - s.a, v2 = p - s.a, v3 = p - s.b;
        if(dcmp(dot(v1, v2)) < 0)       return length(v2);
        else if(dcmp(dot(v1, v3)) > 0)  return length(v3);
        else return abs(cross(v1, v2) / length(v1));
    }

    // returns the shortest distance from segment p to segment q
    Tf distanceSegmentSegment(Segment p, Segment q) {
        if(segmentsIntersect(p, q)) return 0;
        Tf ans = distancePointSegment(p.a, q);
        ans = min(ans, distancePointSegment(p.b, q));
        ans = min(ans, distancePointSegment(q.a, p));
        ans = min(ans, distancePointSegment(q.b, p));
        return ans;
    }

    // returns the projection of point p on line l
    Point projectPointLine(Point p, Line l) {
        static_assert(is_same<Tf, Ti>::value);
        Point v = l.b - l.a;
        return l.a + v * ((Tf) dot(v, p - l.a) / dot(v, v));
    }
}  // namespace Linear

typedef vector<Point> Polygon;
namespace Polygonal {
    // removes redundant colinear points
    // polygon can't be all colinear points
    Polygon RemoveCollinear(const Polygon& poly) {
        Polygon ret;
        int n = poly.size();
        for(int i = 0; i < n; i++) {
            Point a = poly[i];
            Point b = poly[(i + 1) % n];
            Point c = poly[(i + 2) % n];
            if(dcmp(cross(b-a, c-b)) != 0 && (ret.empty() || b != ret.back()))
                ret.push_back(b);
        }
        return ret;
    }

    // returns the signed area of polygon p of n vertices
    Tf signedPolygonArea(const Polygon &p) {
        Tf ret = 0;
        for(int i = 0; i < (int) p.size() - 1; i++)
            ret += cross(p[i]-p[0],  p[i+1]-p[0]);
        return ret / 2;
    }

    // Caution: when all points are colinear AND removeRedundant == false
    // output will be contain duplicate points (from upper hull) at back
    Polygon convexHull(Polygon p, bool removeRedundant = true) {
        int check = removeRedundant ? 0 : -1;
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());

        int n = p.size();
        Polygon ch(n+n);
        int m = 0;      // preparing lower hull
        for(int i = 0; i < n; i++) {
            while(m > 1 && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) <= check) m--;
            ch[m++] = p[i];
        }
        int k = m;      // preparing upper hull
        for(int i = n - 2; i >= 0; i--) {
            while(m > k && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) <= check) m--;
            ch[m++] = p[i];
        }
        if(n > 1) m--;
        ch.resize(m);
        return ch;
    }

    // returns inside = -1, on = 0, outside = 1
    int pointInPolygon(const Polygon &p, Point o) {
        using Linear::onSegment;
        int wn = 0, n = p.size();
        for(int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            if(onSegment(o, Segment(p[i], p[j])) || o == p[i]) return 0;
            int k = dcmp(cross(p[j] - p[i], o - p[i]));
            int d1 = dcmp(p[i].y - o.y);
            int d2 = dcmp(p[j].y - o.y);
            if(k > 0 && d1 <= 0 && d2 > 0) wn++;
            if(k < 0 && d2 <= 0 && d1 > 0) wn--;
        }
        return wn ? -1 : 1;
    }

    // Given a simple polygon p, and a line l, returns (x, y)
    // x = longest segment of l in p, y = total length of l in p.
    pair<Tf, Tf> linePolygonIntersection(Line l, const Polygon &p) {
        using Linear::lineLineIntersection;
        int n = p.size();
        vector<pair<Tf, int>> ev;
        for(int i=0; i<n; ++i) {
            Point a = p[i], b = p[(i+1)%n], z = p[(i-1+n)%n];
            int ora = orient(l.a, l.b, a), orb = orient(l.a, l.b, b), orz = orient(l.a, l.b, z);
            if(!ora) {
                Tf d = dot(a - l.a, l.b - l.a);
                if(orz && orb) {
                    if(orz != orb) ev.emplace_back(d, 0);
                    //else  // Point Touch
                }
                else if(orz) ev.emplace_back(d, orz);
                else if(orb) ev.emplace_back(d, orb);
            }
            else if(ora == -orb) {
                Point ins;
                lineLineIntersection(l, Line(a, b), ins);
                ev.emplace_back(dot(ins - l.a, l.b - l.a), 0);
            }
        }
        sort(ev.begin(), ev.end());

        Tf ans = 0, len = 0, last = 0, tot = 0;
        bool active = false;
        int sign = 0;
        for(auto &qq : ev) {
            int tp = qq.second;
            Tf d = qq.first;    /// current Segment is (last, d)
            if(sign) {          /// On Border
                len += d-last; tot += d-last;
                ans = max(ans, len);
                if(tp != sign) active = !active;
                sign = 0;
            }
            else {
                if(active) {  ///Strictly Inside
                    len += d-last; tot += d-last;
                    ans = max(ans, len);
                }
                if(tp == 0) active = !active;
                else sign = tp;
            }
            last = d;
            if(!active) len = 0;
        }
        ans /= length(l.b-l.a);
        tot /= length(l.b-l.a);
        return {ans, tot};
    }
}  // namespace Polygonal

namespace Convex {
    /// finds the rectangle with minimum area enclosing a convex polygon and
    /// the rectangle with minimum perimeter enclosing a convex polygon
    pair< Tf, Tf >rotatingCalipersBoundingBox(const Polygon &p) {
        using Linear::distancePointLine;
        static_assert(is_same<Tf, Ti>::value);
        int n = p.size();
        int l = 1, r = 1, j = 1;
        Tf area = 1e100;
        Tf perimeter = 1e100;
        for(int i = 0; i < n; i++) {
            Point v = (p[(i+1)%n] - p[i]) / length(p[(i+1)%n] - p[i]);
            while(dcmp(dot(v, p[r%n] - p[i]) - dot(v, p[(r+1)%n] - p[i])) < 0) r++;
            while(j < r || dcmp(cross(v, p[j%n] - p[i]) - cross(v, p[(j+1)%n] - p[i])) < 0) j++;
            while(l < j || dcmp(dot(v, p[l%n] - p[i]) - dot(v, p[(l+1)%n] - p[i])) > 0) l++;
            Tf w = dot(v, p[r%n] - p[i]) - dot(v, p[l%n] - p[i]);
            Tf h = distancePointLine(p[j%n], Line(p[i], p[(i+1)%n]));
            area = min(area, w * h);
            perimeter = min(perimeter, 2 * w + 2 * h);
        }
        return make_pair(area, perimeter);
    }

    // returns the left side of polygon u after cutting it by ray a->b
    Polygon cutPolygon(Polygon u, Point a, Point b) {
        using Linear::lineLineIntersection;
        using Linear::onSegment;

        Polygon ret;
        int n = u.size();
        for(int i = 0; i < n; i++) {
            Point c = u[i], d = u[(i + 1) % n];
            if(dcmp(cross(b-a, c-a)) >= 0) ret.push_back(c);
            if(dcmp(cross(b-a, d-c)) != 0) {
                Point t;
                lineLineIntersection(a, b - a, c, d - c, t);
                if(onSegment(t, Segment(c, d))) ret.push_back(t);
            }
        }
        return ret;
    }

    // returns true if point p is in or on triangle abc
    bool pointInTriangle(Point a, Point b, Point c, Point p) {
        return dcmp(cross(b - a, p - a)) >= 0
            && dcmp(cross(c - b, p - b)) >= 0
            && dcmp(cross(a - c, p - c)) >= 0;
    }

    // pt must be in ccw order with no three collinear points
    // returns inside = -1, on = 0, outside = 1
    int pointInConvexPolygon(const Polygon &pt, Point p) {
        int n = pt.size();
        assert(n >= 3);

        int lo = 1, hi = n - 1;
        while(hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if(dcmp(cross(pt[mid] - pt[0], p - pt[0])) > 0) lo = mid;
            else    hi = mid;
        }

        bool in = pointInTriangle(pt[0], pt[lo], pt[hi], p);
        if(!in) return 1;

        if(dcmp(cross(pt[lo] - pt[lo - 1], p - pt[lo - 1])) == 0) return 0;
        if(dcmp(cross(pt[hi] - pt[lo], p - pt[lo])) == 0) return 0;
        if(dcmp(cross(pt[hi] - pt[(hi + 1) % n], p - pt[(hi + 1) % n])) == 0) return 0;
        return -1;
    }

    // Extreme Point for a direction is the farthest point in that direction
    int extremePoint(const Polygon &poly, Point u) {
        int n = (int) poly.size();
        int a = 0, b = n;
        while(b - a > 1) {
            int c = (a + b) / 2;
            if(dcmp(dot(poly[c] - poly[(c + 1) % n], u)) >= 0 && dcmp(dot(poly[c] - poly[(c - 1 + n) % n], u)) >= 0) {
                return c;
            }

            bool a_up = dcmp(dot(poly[(a + 1) % n] - poly[a], u)) >= 0;
            bool c_up = dcmp(dot(poly[(c + 1) % n] - poly[c], u)) >= 0;
            bool a_above_c = dcmp(dot(poly[a] - poly[c], u)) > 0;

            if(a_up && !c_up) b = c;
            else if(!a_up && c_up) a = c;
            else if(a_up && c_up) {
                if(a_above_c) b = c;
                else a = c;
            }
            else {
                if(!a_above_c) b = c;
                else a = c;
            }
        }

        if(dcmp(dot(poly[a] - poly[(a + 1) % n], u)) > 0 && dcmp(dot(poly[a] - poly[(a - 1 + n) % n], u)) > 0)
            return a;
        return b % n;
    }

    // For a convex polygon p and a line l, returns a list of segments
    // of p that touch or intersect line l.
    // the i'th segment is considered (p[i], p[(i + 1) modulo |p|])
    // #1 If a segment is collinear with the line, only that is returned
    // #2 Else if l goes through i'th point, the i'th segment is added
    // Complexity: O(lg |p|)
    vector<int> lineConvexPolyIntersection(const Polygon &p, Line l) {
        assert((int) p.size() >= 3);
        assert(l.a != l.b);

        int n = p.size();
        vector<int> ret;

        Point v = l.b - l.a;
        int lf = extremePoint(p, rotate90(v));
        int rt = extremePoint(p, rotate90(v) * Ti(-1));
        int olf = orient(l.a, l.b, p[lf]);
        int ort = orient(l.a, l.b, p[rt]);

        if(!olf || !ort) {
            int idx = (!olf ? lf : rt);
            if(orient(l.a, l.b, p[(idx - 1 + n) % n]) == 0)
                ret.push_back((idx - 1 + n) % n);
            else    ret.push_back(idx);
            return ret;
        }
        if(olf == ort) return ret;

        for(int i=0; i<2; ++i) {
            int lo = i ? rt : lf;
            int hi = i ? lf : rt;
            int olo = i ? ort : olf;

            while(true) {
                int gap = (hi - lo + n) % n;
                if(gap < 2) break;

                int mid = (lo + gap / 2) % n;
                int omid = orient(l.a, l.b, p[mid]);
                if(!omid) {
                    lo = mid;
                    break;
                }
                if(omid == olo) lo = mid;
                else hi = mid;
            }
            ret.push_back(lo);
        }
        return ret;
    }
    // [ACW, CW] Tangent
    pair<Point, Point> pointPolyTangents(const Polygon &pt, Point Q) {
        int n = pt.size();
        Point acw_tan = pointPolyTangent(pt, Q, ACW, 0, n - 1);
        Point cw_tan = pointPolyTangent(pt, Q, CW, 0, n - 1);
        return make_pair(acw_tan, cw_tan);
    }
}

namespace Circular {
    // Extremely inaccurate for finding near touches
    // compute intersection of line l with circle c
    // The intersections are given in order of the ray (l.a, l.b)
    vector<Point> circleLineIntersection(Circle c, Line l) {
        static_assert(is_same<Tf, Ti>::value);
        vector<Point> ret;
        Point b = l.b - l.a, a = l.a - c.o;

        Tf A = dot(b, b), B = dot(a, b);
        Tf C = dot(a, a) - c.r * c.r, D = B*B - A*C;
        if (D < -EPS) return ret;

        ret.push_back(l.a + b * (-B - sqrt(D + EPS)) / A);
        if (D > EPS)
            ret.push_back(l.a + b * (-B + sqrt(D)) / A);
        return ret;
    }

    // signed area of intersection of circle(c.o, c.r) &&
    // triangle(c.o, s.a, s.b) [cross(a-o, b-o)/2]
    Tf circleTriangleIntersectionArea(Circle c, Segment s) {
        using Linear::distancePointSegment;
        Tf OA = length(c.o - s.a);
        Tf OB = length(c.o - s.b);

        // sector
        if(dcmp(distancePointSegment(c.o, s) - c.r) >= 0)
            return angleBetween(s.a-c.o, s.b-c.o) * (c.r * c.r) / 2.0;

        // triangle
        if(dcmp(OA - c.r) <= 0 && dcmp(OB - c.r) <= 0)
            return cross(c.o - s.b, s.a - s.b) / 2.0;

        // three part: (A, a) (a, b) (b, B)
        vector<Point> Sect = circleLineIntersection(c, s);
        return circleTriangleIntersectionArea(c, Segment(s.a, Sect[0]))
            + circleTriangleIntersectionArea(c, Segment(Sect[0], Sect[1]))
            + circleTriangleIntersectionArea(c, Segment(Sect[1], s.b));
    }

    // area of intersecion of circle(c.o, c.r) && simple polyson(p[])
    Tf circlePolyIntersectionArea(Circle c, Polygon p) {
        Tf res = 0;
        int n = p.size();
        for(int i = 0; i < n; ++i)
            res += circleTriangleIntersectionArea(c, Segment(p[i], p[(i + 1) % n]));
        return abs(res);
    }

    // locates circle c2 relative to c1
    // interior             (d < R - r)         ----> -2
    // interior tangents (d = R - r)         ----> -1
    // concentric        (d = 0)
    // secants             (R - r < d < R + r) ---->  0
    // exterior tangents (d = R + r)         ---->  1
    // exterior             (d > R + r)         ---->  2
    int circleCirclePosition(Circle c1, Circle c2) {
        Tf d = length(c1.o - c2.o);
        int in = dcmp(d - abs(c1.r - c2.r)), ex = dcmp(d - (c1.r + c2.r));
        return in < 0 ? -2 : in == 0 ? -1 : ex == 0 ? 1 : ex > 0 ? 2 : 0;
    }

    // compute the intersection points between two circles c1 && c2
    vector<Point> circleCircleIntersection(Circle c1, Circle c2) {
        static_assert(is_same<Tf, Ti>::value);

        vector<Point> ret;
        Tf d = length(c1.o - c2.o);
        if(dcmp(d) == 0) return ret;
        if(dcmp(c1.r + c2.r - d) < 0) return ret;
        if(dcmp(abs(c1.r - c2.r) - d) > 0) return ret;

        Point v = c2.o - c1.o;
        Tf co = (c1.r * c1.r + sqLength(v) - c2.r * c2.r) / (2 * c1.r * length(v));
        Tf si = sqrt(abs(1.0 - co * co));
        Point p1 = scale(rotatePrecise(v, co, -si), c1.r) + c1.o;
        Point p2 = scale(rotatePrecise(v, co, si), c1.r) + c1.o;

        ret.push_back(p1);
        if(p1 != p2) ret.push_back(p2);
        return ret;
    }

    // intersection area between two circles c1, c2
    Tf circleCircleIntersectionArea(Circle c1, Circle c2) {
        Point AB = c2.o - c1.o;
        Tf d = length(AB);
        if(d >= c1.r + c2.r) return 0;
        if(d + c1.r <= c2.r) return PI * c1.r * c1.r;
        if(d + c2.r <= c1.r) return PI * c2.r * c2.r;

        Tf alpha1 = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
        Tf alpha2 = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2.0 * c2.r * d));
        return c1.sector(2 * alpha1) + c2.sector(2 * alpha2);
    }

    // returns tangents from a point p to circle c
    vector<Point> pointCircleTangents(Point p, Circle c) {
        static_assert(is_same<Tf, Ti>::value);

        vector<Point> ret;
        Point u = c.o - p;
        Tf d = length(u);
        if(d < c.r) ;
        else if(dcmp(d - c.r) == 0) {
            ret = { rotate(u, PI / 2) };
        }
        else {
            Tf ang = asin(c.r / d);
            ret = { rotate(u, -ang), rotate(u, ang) };
        }
        return ret;
    }

    // returns the points on tangents that touches the circle
    vector<Point> pointCircleTangencyPoints(Point p, Circle c) {
        static_assert(is_same<Tf, Ti>::value);

        Point u = p - c.o;
        Tf d = length(u);
        if(d < c.r) return {};
        else if(dcmp(d - c.r) == 0)     return {c.o + u};
        else {
            Tf ang = acos(c.r / d);
            u = u / length(u) * c.r;
            return { c.o + rotate(u, -ang), c.o + rotate(u, ang) };
        }
    }

    // for two circles c1 && c2, returns two list of points a && b
    // such that a[i] is on c1 && b[i] is c2 && for every i
    // Line(a[i], b[i]) is a tangent to both circles
    // CAUTION: a[i] = b[i] in case they touch | -1 for c1 = c2
    int circleCircleTangencyPoints(Circle c1, Circle c2, vector<Point> &a, vector<Point> &b) {
        a.clear(), b.clear();
        int cnt = 0;
        if(dcmp(c1.r - c2.r) < 0) {
            swap(c1, c2); swap(a, b);
        }
        Tf d2 = sqLength(c1.o - c2.o);
        Tf rdif = c1.r - c2.r, rsum = c1.r + c2.r;
        if(dcmp(d2 - rdif * rdif) < 0) return 0;
        if(dcmp(d2) == 0 && dcmp(c1.r - c2.r) == 0) return -1;

        Tf base = angle(c2.o - c1.o);
        if(dcmp(d2 - rdif * rdif) == 0) {
            a.push_back(c1.point(base));
            b.push_back(c2.point(base));
            cnt++;
            return cnt;
        }

        Tf ang = acos((c1.r - c2.r) / sqrt(d2));
        a.push_back(c1.point(base + ang));
        b.push_back(c2.point(base + ang));
        cnt++;
        a.push_back(c1.point(base - ang));
        b.push_back(c2.point(base - ang));
        cnt++;

        if(dcmp(d2 - rsum * rsum) == 0) {
            a.push_back(c1.point(base));
            b.push_back(c2.point(PI + base));
            cnt++;
        }
        else if(dcmp(d2 - rsum * rsum) > 0) {
            Tf ang = acos((c1.r + c2.r) / sqrt(d2));
            a.push_back(c1.point(base + ang));
            b.push_back(c2.point(PI + base + ang));
            cnt++;
            a.push_back(c1.point(base - ang));
            b.push_back(c2.point(PI + base - ang));
            cnt++;
        }
        return cnt;
    }
}  // namespace Circular

namespace EnclosingCircle{
    // returns false if points are collinear, true otherwise
    // circle p touch each arm of triangle abc
    // circle p touch each arm of triangle abc
    bool inCircle(Point a, Point b, Point c, Circle &p) {
        using Linear::distancePointLine;
        static_assert(is_same<Tf, Ti>::value);
        if(orient(a, b, c) == 0) return false;
        Tf u = length(b - c);
        Tf v = length(c - a);
        Tf w = length(a - b);
        p.o = (a * u + b * v + c * w) / (u + v + w);
        p.r = distancePointLine(p.o, Line(a, b));
        return true;
    }

    // returns false if points are collinear, true otherwise
    // circle p goes through points a, b && c
    bool circumCircle(Point a, Point b, Point c, Circle &p) {
        using Linear::lineLineIntersection;
        if(orient(a, b, c) == 0) return false;
        Point d = (a + b) / 2, e = (a + c) / 2;
        Point vd = rotate90(b - a), ve = rotate90(a - c);
        bool f = lineLineIntersection(d, vd, e, ve, p.o);
        if(f) p.r = length(a - p.o);
        return f;
    }

    /// finds a circle that goes through all points in p, |p| <= 3.
    Circle boundary(const vector<Point> &p) {
        Circle ret;
        int sz = p.size();
        if(sz == 0)         ret.r = 0;
        else if(sz == 1)    ret.o = p[0], ret.r = 0;
        else if(sz == 2)    ret.o = (p[0] + p[1]) / 2, ret.r = length(p[0] - p[1]) / 2;
        else if(!circumCircle(p[0], p[1], p[2], ret))    ret.r = 0;
        return ret;
    }

    /// Min circle enclosing p[fr.....n-1], with points in b
    /// on the boundary of the circle, |b| <= 3.
    Circle welzl(const vector<Point> &p, int fr, vector<Point> &b) {
        if(fr >= (int) p.size() || b.size() == 3)   return boundary(b);

        Circle c = welzl(p, fr + 1, b);
        if(!c.contains(p[fr])) {
            b.push_back(p[fr]);
            c = welzl(p, fr + 1, b);
            b.pop_back();
        }
        return c;
    }
    /// Minimum enclosing circle of p, using weizl's algo.
    /// Complexity: amortized O(n).
    Circle MEC(vector<Point> p) {
        random_shuffle(p.begin(), p.end());
        vector<Point> q;
        return welzl(p, 0, q);
    }
}