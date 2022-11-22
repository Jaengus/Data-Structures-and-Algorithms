void move(int n, int a, int c, int b)
{
  if (n > 0)
  {
    move(n - 1, a,  b, c);
    std::cout << "Move disk " << n << " from " << a << " to " << c << ".\n";
    move(n - 1, b, c, a);
  }
}
