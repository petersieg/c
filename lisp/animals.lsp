;
; Animals Game
; from Lisp in Small Parts, http://lisp.plasticki.com/
; Licensed under CC0 1.0: http://creativecommons.org/publicdomain/zero/1.0/
; 20th February 2011
;

(defparameter animals-tree '("Does it live in the sea?" "a dolphin" "a horse"))

(defun animals (tree)
  (if (listp tree)
      (ask-question tree)
    (make-guess tree)))

(defun ask-question (tree)
  (if (capi:prompt-for-confirmation (first tree))
      (list (first tree) (animals (second tree)) (third tree))
    (list (first tree) (second tree) (animals (third tree)))))

(defun make-guess (animal)
  (if (capi:prompt-for-confirmation (format nil "Is it ~a?" animal))
      (progn
        (capi:display-message "Ho ho!")
        animal)
    (learn-animal animal (capi:prompt-for-string "What were you thinking of?"))))

(defun learn-animal (animal new-animal)
  (let ((question
         (capi:prompt-for-string
          (format nil "Give me a yes/no question to distinguish between ~a and ~a" 
                  new-animal animal))))
    (if (capi:prompt-for-confirmation 
         (format nil "What would the answer be for ~a?" new-animal))
        (list question animal new-animal))
    (list question new-animal animal)))

(defun play-animals ()
  (setf animals-tree (animals animals-tree)))

; Version that saves the tree to disk

(defun play-animals ()
  (when (probe-file "tree")
    (with-open-file (stream "tree" :direction :input)
      (setq animals-tree (read stream))))
  (setq animals-tree (animals animals-tree))
  (with-open-file (stream "tree" :direction :output :if-exists :supersede)
    (write animals-tree :stream stream)))
