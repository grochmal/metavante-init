def integralcos(a, b)
  x1 = a
  y1 = Math.cos x1
  integral = 0
  while((x2 = x1 +0.001) < b)
    y2 = Math.cos x2
    py = (y1 + y2)/2
    integral = integral + py*0.001
    x1 = x2
    y1 = y2
  end
  x2 = b
  y2 = Math.cos x2
  integral = integral + (y1 + y2)*0.001/2
  return integral
end

puts integralcos(1.57, 4.71)
