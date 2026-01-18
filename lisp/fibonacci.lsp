(define fib (lambda (n) (if (< n 2) n (+ (fib (- n 1)) (fib (- n 2))))))

(define k-v (lambda (r) ( / (* r r r 3.14159 4) 3 ))) ; kugel-volumen

(define k-f (lambda (r) (* r r 3.14159))) ; kugel-flaeche
