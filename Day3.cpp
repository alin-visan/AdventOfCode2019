#include "stdafx.h"
#include "Day3.h"

void Day3::Solve()
{
  Part1();
  Part2();
}

void Day3::Part1()
{
  ifstream fin;
  fin.open(FileIn);

  ofstream fout;
  fout.open(FileOut);

  if (!fin.is_open() || !fout.is_open())
    return;

  vector<Wire> wires;

  while (fin.good())
  {
    char line[2048];
    fin.getline(line, _countof(line));

    wires.push_back(BuildWire(GetDirections(line)));
  }
  fin.close();

  fout.clear();
  fout << ClosestDist(GetIntersectionPoints(wires[0], wires[1])) << '\n';
  fout.flush();

  fout.close();
}
void Day3::Part2()
{
  ifstream fin;
  fin.open(FileIn);

  ofstream fout;
  fout.open(FileOut, ofstream::out | ::ofstream::app);

  if (!fin.is_open() || !fout.is_open())
    return;

  vector<Wire> wires;

  while (fin.good())
  {
    char line[2048];
    fin.getline(line, _countof(line));

    wires.push_back(BuildWire(GetDirections(line)));
  }
  fin.close();

  fout << GetFewestSteps(wires[0], wires[1]) << '\n';
  fout.flush();

  fout.close();
}

vector<pair<char, short>> Day3::GetDirections(string s) const
{
  vector<pair<char, short>> localDirections;

  if (s.empty())
    return localDirections;

  int pos = 0;
  string local;

  while (pos < s.size())
  {
    if (s[pos++] != ',')
      local.append(s[pos-1] + string());
    else
    {
      localDirections.push_back({ local[0], stoi(local.substr(1)) });
      local.clear();
    }
  }

  return localDirections;
}

int Day3::ManhDist(Point p1, Point p2)
{
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

vector<Day3::Point> Day3::GetIntersectionPoints(const Wire& w1, const Wire& w2)
{
  vector<Point> local;
  for (const auto& p : w1.points)
  {
    for (const auto& pp : w2.points)
    {
      if (p == pp)
        local.push_back(p);
    }
  }
  return local;
}

Day3::Wire Day3::BuildWire(const vector<pair<char, short>>& directions)
{
  Wire local;

  if (directions.empty())
    return local;

  Point center{ 0,0 };
  local.points.push_back(center);

  int x = 0;
  int y = 0;

  for (const auto& d : directions)
  {
    const auto & dir = d.first;
    const auto & steps = d.second;

    if (dir == 'R')
    {
      for (int i = 1; i <= steps; i++)
        local.points.push_back({++x, y});
    }
    else if (dir == 'L')
    {
      for (int i = 1; i <= steps; i++)
        local.points.push_back({ --x, y });
    }
    else if (dir == 'U')
    {
      for (int i = 1; i <= steps; i++)
        local.points.push_back({ x, ++y });
    }
    else if (dir == 'D')
    {
      for (int i = 1; i <= steps; i++)
        local.points.push_back({ x, --y });
    }
  }
  return local;
}

int Day3::ClosestDist(const vector<Point>& points)
{
  int min = 1000000;
  for (size_t i = 1; i < points.size(); i++)
  {
    int manhDist = ManhDist({ 0,0 }, points[i]);
    if (manhDist < min)
      min = manhDist;
  }
  return min;
}

int Day3::GetFewestSteps(const Wire& w1, const Wire& w2) const
{
  int minSteps = 1000000;
  for (size_t i = 1; i < w1.points.size(); i++)
  {
    for (size_t j = 2; j <  w2.points.size(); j++)
    {
      
      if (w1.points[i] == w2.points[j])
      {
        if (i + j < minSteps)
          minSteps = i + j;
      }
    }
  }
  return minSteps;
}