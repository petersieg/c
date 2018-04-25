;
; Anagram Solver
; from Lisp in Small Parts, http://lisp.plasticki.com/
; Licensed under CC0 1.0: http://creativecommons.org/publicdomain/zero/1.0/
; 2nd July 2012
;

; First we read in the wordlist

(defparameter wordlist 
  (with-open-file (stream (capi:prompt-for-file "Wordlist:" :operation :open))
    (read stream)))

; The anagram dictionary is a hash table

(defparameter dict (make-hash-table :test 'string=))

; Make anagrams

(defun sorted (word)
  (sort (copy-seq word) 'char<))

; Add word to the dictionary

(defun add-word (word)
  (let* ((sword (sorted word)))
    (setf (gethash sword dict) (cons word (gethash sword dict)))))

; Add all words

(defun add-words-to-dict (wlist)
  (if (null wlist) nil
    (let ((word (first wlist)))
      (add-word word)
      (add-words-to-dict (rest wlist)))))

; Find anagram

(defun find-anagram (word)
  (gethash (sorted word) dict))

(defun anagram ()
  (capi:prompt-with-list
   (find-anagram (capi:prompt-for-string "Find anagram:"))
   "Anagrams"))
