#ifndef __TEST__
#define __TEST__

#include "Convex_Hull.hpp"

class Test
{
    public:
        static void test_1()
        {
            int n; cin >> n;
            Vertices<int> vertices(n);

            I_Points points = vertices.Convex_Hull();

            for (const I_Point& point : points)
                cout << point.x << ' ' << point.y << endl;
        }

        static void test_2()
        {
            int n; cin >> n;
            Vertices<long> vertices(n);

            L_Points points = vertices.Convex_Hull();

            for (const L_Point& point : points)
                cout << point.x << ' ' << point.y << endl;
        }

        static void test_3()
        {
            int n; cin >> n;
            Vertices<float> vertices(n);
            
            F_Points points = vertices.Convex_Hull();

            for (const F_Point& point : points)
                cout << point.x << ' ' << point.y << endl;
        }
};

#endif