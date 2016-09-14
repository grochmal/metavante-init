
c = ['r','g','b']
all_pos = [(f,g,a,t,m) | f <- c, g <- c, a <- c, t <- c, m <- c
		       , f /= g, f /= a, g /= a, g /= t, a /= t
		       , a /= m, t /= m
		       ]

