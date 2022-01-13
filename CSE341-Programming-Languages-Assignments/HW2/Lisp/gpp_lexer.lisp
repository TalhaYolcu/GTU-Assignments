
;;This function tokenizes the given identifier							
(defun tokenize-identifier (token lst)
	(assert (is-alphabet-char (string (char token 0))))
	;; Scanning
	(loop for c across token 
		do (if (not (or (is-alphabet-char c) (is-numericp c))) 
		(return-from tokenize-identifier (errout token c))))

	(let ((kw (tokenize-kw token lst)))
		(if (null kw) (format nil "IDENTIFIER") kw))
)

;;This function tokenizes the given value finds integer value of the given input
(defun tokenize-value (token)
	(assert (is-numeric-char (string (char token 0))))

	;; is value 0?
	(if (and (> (length token) 1) (is-zero-char (substring token 0 1))) 
		(return-from tokenize-value (errout token (substring token 0 1))))

	;; find the value
	(loop for c across token 
		do (if (not (is-numeric-char c))
		(return-from tokenize-value (errout token c))))
	(format nil "VALUE")
)

;;This function tokenizes the kw words
(defun tokenize-kw (token lst)
	 (let ((value (assoc token lst :test #'string=)))
		(if value (format nil "~a" (cdr value)) nil))
)

;;This function tokenizes the operators
(defun tokenize-op (token lst)
	 (let ((value (assoc token lst :test #'string=)))
		(if value (format nil "~a" (cdr value)) nil))
)

;;This function tokenizes the given string
(defun tokenize-string (token)
	(assert (is-quomark-char (string (char token 0))))
	(format nil "STRING")
)


;;This function helps us to detect syntax error
(defun errout (token c)
	(format nil "SYNTAX ERROR: '~a' : '~a'" token c)
)

;;This function deterimies whether the given character is 0 or not
(defun is-zero-char (chr)
	(eq (char-code (coerce chr 'character)) 48)
)

;;This function deterimies whether the given character is semicolon or not
;;(defun is-semicolon-char (chr)
;;	(eq (char-code (coerce chr 'character)) 59)
;;)

;;This function deterimies whether the given character is quation mark or not
(defun is-quomark-char (chr)
	(eq (char-code (coerce chr 'character)) 34)
)

;;This function deterimies whether the given character is a number or not
(defun is-numeric-char (chr)
	(let ((c (char-int (coerce chr 'character))))
		(and (>= c (char-int #\0)) (<= c (char-int #\9))))
)
;;This function determines given char is alpabet char or not	
(defun is-alphabet-char (chr)
	(let ((c (char-int (coerce chr 'character))))
		(and (>= c (char-int #\A)) (<= c (char-int #\z))))
)

;;This function determines the tokens of the language
(defun get-token-lst ()
	(let((token-key '("and" "or" "not" "equal" "less" "nil" "list"
	 	 			 	"append" "concat" "set" "deffun" "for" "if" 
	 	 			 	"exit" "load" "disp" "true" "false" "+" "-" 
	 	 			 	"/" "*" "(" ")" "**" "," "defvar" "while" "load"))
		 (token-value '("KW_AND" "KW_OR" "KW_NOT" "KW_EQUAL" "KW_LESS" "KW_NIL" "KW_LIST"
		 				"KW_APPEND" "KW_CONCAT" "KW_SET" "KW_DEFFUN" "KW_FOR" "KW_IF" 
					   	"KW_EXIT" "KW_LOAD" "KW_DISP" "KW_TRUE" "KW_FALSE" "OP_PLUS" "OP_MINUS"
					   	"OP_DIV" "OP_MULT" "OP_OP" "OP_CP" "OP_DBLMULT" "OP_COMMA" "KW_DEFVAR" "KW_WHILE" "KW_LOAD")))
		(pairlis token-key token-value))
)

;;This function helps us to tokenize tokens
(defun tokenize (token lst)
	 ;; Scan the first char and direct it to proper state.
	 (let ((c (string (char token 0)))) 
	 (cond ((is-alphabet-char c) (tokenize-identifier token lst))  ;; [a-zA-z] identifier and kw
	 	   ((is-numeric-char c) (tokenize-value token))			;; [0-9] value
	 	   ((is-quomark-char c) (tokenize-string token))
	 	   (t (if (tokenize-op token lst) 					;; operator
	 	   (tokenize-op token lst) (errout token c)))))
)	;; else, syntax error.	

;;This function checks whether input char is space or not
(defun is-space-char (c) (char= c #\Space))

;;This function takes a list and splits elements with space
(defun split-seq-with-space (string &key (is-space-char #'is-space-char))
  (loop :for start = (position-if-not is-space-char string)
    :then (position-if-not is-space-char string :start (1+ end))
    :for end = (and start (position-if is-space-char string :start start))
    :when start :collect (subseq string start end)
    :while end)
)

;;cleans the given input from spaces newlines,backpspaces,tabs and returns
(defun remove_unnecessary_parts (str)
	(let ((trim-lst '(#\Space #\Newline #\Backspace #\Tab #\Return )))
	(string-trim trim-lst str))
)

;;checks whether character is ( or ) ascii numbers of ( and ) are 40 and 41
(defun is-op-cp (chr)
	(let ((c (char-int (coerce chr 'character))))
		(or (= c 40) (= c 41)))
)

;;generates a list from given string
(defun list-to-string (lst)
    (format nil "~{~A~}" lst)
)

;; This function creates a list from the given input, it generates tokens
(defun create-input-list (str)
	;; get the string from the list to handle some spaces
	(setq str (list-to-string 
		(map 'list #'(
			lambda (c) 
				(if (is-op-cp c) (concatenate 'string " " (string c) " ") (string c)))
		(remove_unnecessary_parts str)))
	)
	;; in sequence, find the indices of spaces in between quo-mark
	(let ((created_list (loop for index from 0 to (- (length str) 1)
			    when (char= (aref str index) #\") collect index))
		  (index1 '()) (index2 '()) (space-index '())
		)
	(loop while created_list do (setq index1 (car created_list)) 
					do (setq index2 (car (cdr created_list)))
					do (setq created_list (cdr (cdr created_list)))
					do (setq space-index
		 	(loop for index from 0 to (- (length str) 1)
			when (and (> index index1) (< index index2) (char= (aref str index) #\Space)) 
			collect index)))

	;; connect the string in between quo-marks with dots.
	;; turn the string to list with #Space delimeter.
	(split-seq-with-space (list-to-string
	(loop for index from 0 to (- (length str) 1)
		if (member index space-index) collect #\. else collect (aref str index))))
	)
)