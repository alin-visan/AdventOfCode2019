#pragma once

class Day3
{
public:
  struct Point
  {
    int x{ 0 };
    int y{ 0 }; 

    friend bool operator==(const Point & p1, const Point & p2)
    {
      return (p1.x == p2.x) && (p1.y == p2.y);
    }
  };

  struct Wire
  {
    vector<Point> points;
  };
  
  void Solve();

private:
  void Part1();
  void Part2();
  
  vector<pair<char, short>> GetDirections(string s) const;
  int ManhDist(Point p1, Point p2);
  vector<Point> GetIntersectionPoints(const Wire & w1, const Wire & w2);
  Wire BuildWire(const vector<pair<char, short>>& directions);
  int ClosestDist(const vector<Point>& points);
  int GetFewestSteps(const Wire & w1, const Wire & w2) const;
};