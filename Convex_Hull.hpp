#ifndef __CONVEX_HULL__
#define __CONVEX_HULL__

#include "lib_file.hpp"

temp_Comp class Vertex
{
    public:
        Comparable x, y;
        Vertex(const Comparable& x, const Comparable& y) : x(x), y(y) {}
};

temp_Comp class Vertices
{    
    public:
        // Constructors
        Vertices(int n = 10)
        {
            for (int i = 0; i < n; i++)
            {  
                Comparable x, y;
                cin >> x >> y;
                E.push_back(Point(x, y));
            }
        }

        // Methods
        Points Convex_Hull() const
        {
            return Convex_Hull(E);
        }

    private:
        // Attribute
        Points E;

        /* Private Methods */

        // Tìm vỏ lồi
        Points Convex_Hull(const Points& E) const
        {
            pair_Int id_PQ = P_and_Q(E);
            if (E[id_PQ.first].x == E[id_PQ.second].x)
                return E;
            
            Points Eo, Eoo;
            divide_vertices(E, Eo, Eoo, E[id_PQ.first], E[id_PQ.second]);
            Points res = merger(half_convex_hull(Eo, E[id_PQ.first], E[id_PQ.second]), half_convex_hull(Eoo, E[id_PQ.second], E[id_PQ.first]));
            res.pop_back();
            return res;
        }

        // Tính P và Q
        pair_Int P_and_Q(const Points& E) const
        {
            int id_xmin = 0, id_xmax = 0;
            for (int i = 1; i < E.size(); i++)
            {
                if (E[i].x < E[id_xmin].x) id_xmin = i;
                if (E[i].x > E[id_xmax].x) id_xmax = i;
            }

            return pair_Int(id_xmin, id_xmax);
        }

        // Tính Eo và E'o
        void divide_vertices(const Points& E, Points& Eo, Points& Eoo, const Point& P, const Point& Q) const
        {
            pair_Comp norm_vt = norm(P, Q);
            for (const Point& point : E)
            {
                const Comparable res = line_value(norm_vt, point, P);
                if (res >= 0) Eo.push_back(point);
                if (res <= 0) Eoo.push_back(point);
            }
        }

        // Làm việc trên nửa vỏ
        Points half_convex_hull(const Points& E, const Point& P, const Point& Q) const
        {
            if (E.size() == 2) return E;
        
            Point S = find_S(E, P, Q);
            Points E1, E1o;
            divide_E1_and_E1o(E, E1, E1o, P, S, Q);
            
            return merger(half_convex_hull(E1, P, S), half_convex_hull(E1o, S, Q));
        }

        // Tìm chỉ số của S
        Point find_S(const Points& E, const Point& P, const Point& Q) const
        {
            pair_Comp norm_vt = norm(P, Q);
            int idx;
            Comparable max_distance = 0;
            for (int i = 0; i < E.size(); i++)
            {
                Comparable cur_distance = abs(line_value(norm_vt, E[i], P));
                if (cur_distance > max_distance)
                {
                    max_distance = cur_distance;
                    idx = i;
                }
            }

            return E[idx];
        }

        // Tìm nửa bao lồi
        void divide_E1_and_E1o(const Points& E, Points& E1, Points& E1o, const Point& P, const Point& S, const Point& Q) const
        {
            pair_Comp norm_vt_E1 = norm(P, S);
            Comparable oriented_Q = line_value(norm_vt_E1, Q, S);
            pair_Comp norm_vt_E1o = norm(S, Q);
            Comparable oriented_P = line_value(norm_vt_E1o, P, S);

            E1.push_back(P); E1.push_back(S);
            E1o.push_back(S); E1o.push_back(Q);
            for (const Point& point : E)
            {
                Comparable cur_oriented = line_value(norm_vt_E1, point, S);
                if (cur_oriented * oriented_Q < 0 and abs(cur_oriented) > ESP) E1.push_back(point);
                cur_oriented = line_value(norm_vt_E1o, point, S);
                if (cur_oriented * oriented_P < 0 and abs(cur_oriented) > ESP) E1o.push_back(point);
            }
        }

        // Nối 2 vỏ lại
        Points merger(const Points& Eo, const Points& Eoo) const
        {
            Points Hull;
            for (const Point& point : Eo) Hull.push_back(point);
            for (int i = 1; i < Eoo.size(); i++) Hull.push_back(Eoo[i]);

            return Hull;
        }

        // Tìm vector chỉ phương
        inline pair_Comp norm(const Point& P, const Point& Q) const
        {
            return pair_Comp(Q.y - P.y, P.x - Q.x);
        }

        // Tìm khoảng cách
        inline Comparable line_value(const pair_Comp& norm_vt, const Point& A, const Point& B) const
        {
            return norm_vt.first * (A.x - B.x) + norm_vt.second * (A.y - B.y);
        }
};

#endif
