#include<bits/stdc++.h>

class Point{
    public:
    int x,y;
    bool visited=false;
    bool operator ==(const Point& other){
        return x==other.x&&y==other.y;
    }
    friend std::ostream& operator <<(std::ostream& out, const Point& p);
    size_t operator()( const Point& k ) const
    {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + std::hash<int>()( k.x );
            res = res * 31 + std::hash<int>()( k.y );
            return res;
    }

};
namespace std
{
    template <>
    struct hash<Point>
    {
        size_t operator()( const Point& k ) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + hash<int>()( k.x );
            res = res * 31 + hash<int>()( k.y );
            return res;
        }
    };
}