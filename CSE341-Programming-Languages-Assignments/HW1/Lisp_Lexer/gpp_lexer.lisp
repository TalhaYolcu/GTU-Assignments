;;TOKENS
(defvar KW (list "KW_AND" "KW_OR" "KW_NOT" "KW_EQUAL" "KW_LESS" "KW_NIL" "KW_LIST" "KW_APPEND" "KW_CONCAT" "KW_SET" "KW_DEFFUN" "KW_FOR" "KW_IF" "KW_EXIT" "KW_LOAD" "KW_DISP" "KW_TRUE" "KW_FALSE"))
(defvar OP (list "OP_PLUS" "OP_MINUS" "OP_DIV" "OP_DBLMULT" "OP_MULT" "OP_OP" "OP_CP" "OP_OC" "OP_CC" "OP_COMMA"))
(defvar keywords (list "and" "or" "not" "equal" "less" "nil" "list" "append" "concat" "set" "deffun" "for" "if" "exit" "load" "disp" "true" "false"))
(defvar operators (list "+" "-" "/" "**" "*" "(" ")" "\"" "\"" ","))
(defvar opencloseparanthesis-escape (list "(" ")" "\""))
(defvar symbols (list "\n" "\t" " "))
(defvar comment ";")
(defvar tokens (list))
(defvar opoc 0)


;;This function takes input from the command line
(defun take_input()
    (setq command (read-line))  ;;take input from command line
    (terpri)                    ;;newline
    (defvar mode -4)            ;;set error by default
    (if (< (length command) 16 )    ;;if input length is less than 16, means that error
        (setq mode -4)              
        (if (equal command "(gppinterpreter)")      ;;else if it is just gppinterpreter than we are not gonna read a file
            (setq mode 2)                           ;;set mode to 2
            (setq mode 4)                           ;;we are gonna read a file
        )
    )
    (if (= mode 2) (gppinterpreter))                ;;we are not gonna read file
    (if (= mode -4) (write "WRONG INPUT TRY AGAIN..."))     ;;we have error
    (if (= mode 4) (gppinterpreter (subseq command 16 (get-length-minus-one command ))))            ;;we are gonna read file and we have to seperate .txt) from .txt and )

)
;Reads input from a file
(defun read-from-file (filename)
    (format t "READ FROM FILE~%")
    (let ((input_file (open filename :if-does-not-exist nil)))          ;;open the file
        (when input_file
            (loop for line = (read-line input_file nil)         ;;read the line from input file
            while line do (parse_line line))                    ;;parse the line into tokens
            (close input_file)
        )
    )    
)

;Reads input from terminal
(defun read-from-terminal ()
    (format t "READ FROM TERMINAL~%")
    (let ((command_line) (control))
        (loop 
            (setq command_line (read-line))             ;;read the line
            (setq control (parse_line command_line))    ;;parse the line into tokens
            (terpri)
            (when (= control -1) (return))              ;;exit if we are gonna terminate
        )
    )    
)
(defun gppinterpreter (&optional filename)              ;;needed gppinterpreter function
    (if (equal filename nil)
        (read-from-terminal)
        (read-from-file filename)
    )
)
(defun parse_line (line)
	(let ((words) (foo 0) (tempword))
		(setq line (string-trim '(#\Space #\Tab #\Newline) line))       ;; trim the unwanted parts
		(setq tokens (seperate-string line))                             ;;  seperate string into words
		(loop for tok in tokens                     
			do
			(progn
				(setq tempword (string-trim '(#\Space #\Tab #\Newline) tok))        ;;again trim the unwanted parts
				(setq foo (handleword tempword))                                     ;;handle the tempword and return a result to see we are finished or not
				(if (or (= foo 2) (= foo -1)) (return foo))
			)
		)
		foo		
	)
)
;;this functions handles a one word at a time
(defun handleword (word)
	(let ((len (length word)) (subword) (counter2 0) (handler_resulter3) (temp) (check 0) (id 0))
		(loop for counter3 from 1 to len
			do
			(progn
				(if (= check 1) (setq check 0) )
				(setq subword (string-downcase (subseq word counter2 counter3)))

				;; Check wheter subword is operator or not.
				(if (= check 0)
					(progn
						(setq handler_resulter3 (findinList subword operators))
						(if (not (equal handler_resulter3 nil))
							(progn
								(if (equal handler_resulter3 4)
									(if (and (< counter3 len) (string= (subseq word counter3 (+ counter3 1)) "*")) (setq handler_resulter3 3))
								)
								(if (equal handler_resulter3 7) (progn (setq handler_resulter3 (+ handler_resulter3 (mod opoc 2))) (setq opoc (+ opoc 1))))
							
								(if (or (equal handler_resulter3 5) (equal handler_resulter3 6) (equal handler_resulter3 7) (equal handler_resulter3 9))
									(progn (setq tokens (append tokens (list subword))) (write (nth handler_resulter3 OP)) (terpri) (setq counter2 counter3) (setq check 1))
									
									(if (>= counter3 len)
										(progn (setq tokens (append tokens (list subword))) (write (nth handler_resulter3 OP)) (terpri) (setq check 1))
										(progn
										 	(setq temp (subseq word counter3 (+ counter3 1)))
										 	(if (equal (findinList temp opencloseparanthesis-escape) nil)
										 		(progn (setq check -1) (format t "Syntax error ~S , it cant be tokenized." (subseq word counter2 len)) (terpri))
										 		(progn (setq tokens (append tokens (list subword))) (write (nth handler_resulter3 OP)) (terpri) (setq counter2 counter3) (setq check 1))
										 	)
										)
									)	
								)
							)	
						)
					)	
				)
				(if (= check 0)
					(progn
						(setq handler_resulter3 (findinList subword keywords))
						(if (not (equal handler_resulter3 nil))
							(if (>= counter3 len)
								(progn (setq tokens (append tokens (list subword))) (write (nth handler_resulter3 KW)) (terpri) (setq check 1))
								(progn
								 	(setq temp (subseq word counter3 (+ counter3 1)))
								 	;; After these keywords, Only possible (defined above) tokens can come.
								 	(if (and (equal (findinList temp opencloseparanthesis-escape) nil))
								 		(if (equal (isidenitifer (concatenate 'string subword temp)) nil) 
								 			(progn (setq check -1) (format t "Syntax error ~S , it cant be tokenized." (subseq word counter2 len)) (terpri))
								 		)
								 		(progn (setq tokens (append tokens (list subword))) (write (nth handler_resulter3 KW)) (terpri) (setq counter2 counter3) (setq check 1))
								 	)
								)
							)
						)
					)	
				)
				(if (= check 0)
					(progn
						(setq handler_resulter3 (isValue subword))
						(if (not (equal handler_resulter3 nil))
							(progn
								(loop
									(setq temp (string-downcase (subseq word counter2 counter3)))
									(setq counter3 (+ counter3 1))
									(when (or (equal (isValue temp) nil) (> counter3 len)) (return))
								)
								(setq counter3 (- counter3 1))
								(if (equal (isValue temp) nil) (setq counter3 (- counter3 1)))								
								(if (>= counter3 len)
									(progn (setq tokens (append tokens (list subword))) (write "VALUE") (terpri) (setq check 1))
									(progn
									 	(setq temp (subseq word counter3 (+ counter3 1)))
									 	(if (equal (findinList temp opencloseparanthesis-escape) nil)
									 		(progn (setq check -1) (format t "Syntax error ~S , it cant be tokenized." (subseq word counter2 len)) (terpri))
									 		(progn (setq tokens (append tokens (list subword))) (write "VALUE") (terpri) (setq counter2 counter3) (setq check 1))
									 	)
									)
								)
							)	
						)
					)
				)
				(if (and (= check 0) (string= subword comment))
						(if (and (< counter3 len) (string= (subseq word counter3 (+ counter3 1)) comment))
							(progn (setq tokens (append tokens (list "COMMENT"))) (write "COMMENT") (terpri) (setq counter2 counter3) (setq check 2))
						)
				)
				(if (= check 0)
					(progn
						(setq handler_resulter3 (isidenitifer subword))
						(if (equal handler_resulter3 t)
							(if (= counter3 len)
								(progn (setq tokens (append tokens (list subword))) (write "IDENTIFIER") (terpri)  (setq check 1))
								(progn
									(setq temp (string-downcase (subseq word counter2 (+ counter3 1))))
									(setq id (isidenitifer temp))
									(if (equal handler_resulter3 id)
										()
										(progn
										 	(setq temp (subseq word counter3 (+ counter3 1)))
										 	(if (equal (findinList temp opencloseparanthesis-escape) nil)
										 		(progn (setq check -1) (format t "Syntax error ~S , it cant be tokenized." (subseq word counter2 len)) (terpri))
										 		(progn (setq tokens (append tokens (list subword))) (write "IDENTIFIER") (terpri) (setq counter2 counter3) (setq check 1))
										 	)
										)
									)
								)
							)
							(progn (setq check -1) (format t "Syntax error ~S , it cant be tokenized." (subseq word counter2 len)) (terpri))
						)
					)	
				)
				(setq check (evaluate_the_result check))
				(if (or (= check -1) (= check 2)) (return check))
			)
		)
		check			
	)
)
;;this function takes a seperator and seperates it into parts
(defun seperate-string (string &optional (separator " "))
  (seperate-2 string separator))
;;this function helper function to seperate
(defun seperate-2 (string &optional (separator " ") (r nil))
  (let ((n (position separator string
		     :from-end t
		     :test #'(lambda (x y)
			       (find y x :test #'string=)))))
    (if n
	(seperate-2 (subseq string 0 n) separator (cons (subseq string (1+ n)) r))
      (cons string r)))
      )
;;this function find the given thing in the list
(defun findinList (word complist &optional (counter3 0))
	(if (null complist)
		nil
		(if (string= word (car complist))
			counter3
			(findinList word (cdr complist) (+ counter3 1))
		)
	)
)
;; is this word is an identifier
(defun isidenitifer (word)
	(let ((len (- (length word) 1)) (chr) (identifier_result t))

		(loop for counter3 from 0 to len
			do
			(progn
				(setq chr (char word counter3))
				(if (= counter3 0)
					(if (or (alpha-char-p chr) (char= chr #\_)) (setq identifier_result t) (setq identifier_result nil))
					(if (or (alpha-char-p chr) (digit-char-p chr) (char= chr #\_)) () (setq identifier_result nil))
				)
				(if (equal identifier_result nil) (return identifier_result))
			)
		)
		identifier_result
	)
)
;;this function returns a result according to token situation
(defun evaluate_the_result (check)
	(let ((len (list-length tokens)) (evaluation_result check))

		(if (> len 2)
			(if (and (string= (nth (- len 3) tokens) "(") (string= (nth (- len 2) tokens) "exit")  (string= (nth (- len 1) tokens) ")")) (setq evaluation_result -1))
		)
		evaluation_result
	)
)

;; is this word a value
(defun isValue (word)
	(let ((chr) (my_val t))
		(if (equal (every #'digit-char-p word) nil)
			(setq my_val nil)
			(progn
				(if (= (length word) 1)
					(setq my_val t)
					(progn
						(setq chr (char word 0))
						(if (equal (digit-char-p chr) 0) (setq my_val nil) (setq my_val t))
					)
				)		
			)
		)
		my_val	
	)
)
;;this function gives the length of string - 1
(defun get-length-minus-one(str)
    (defvar len (length str))
    (- len 1)
)
;;main function
(defun main()
    (format t "PLEASE READ README FILE~%")
    (format t "(gppinterpreter) to read from terminal~%")
    (format t "(gppinterpreter file.gpp) to read from a file~%")
    (take_input)

)
;;;; MAIN FUNCTION
(main)


