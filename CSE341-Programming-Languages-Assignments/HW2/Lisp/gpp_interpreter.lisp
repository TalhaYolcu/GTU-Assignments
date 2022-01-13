(defvar *vars* (make-hash-table :test 'equal))

;;This function performs the math operation
(defun perform-math-operation (op1 op2 op)
	(let ((num1 op1) (num2 op2)) 
	(cond ((string= "+" op) (+ num1 num2))
		  ((string= "-" op) (- num1 num2))
		  ((string= "*" op) (* num1 num2))
		  ((string= "/" op) (/ num1 num2))
		  ((string= "**" op) (expt num1 num2))		  
		  )
	)
)

;;This function performs the boolean operations
(defun perform-bool-operation (op op1 &optional op2)
	(if (and op2 (string= "less" op) (and (integerp op1) 
		(integerp op2)))
		(if (< op1 op2) 
			(return-from perform-bool-operation "true")
			(return-from perform-bool-operation "false"))
	)		
	(if (and op2 (string= "equal" op) (and (integerp op1) 
		(integerp op2)))
		(if (= op1 op2) 
			(return-from perform-bool-operation "true")
			(return-from perform-bool-operation "false"))
	)
	(if (let ((var1 (get-bool-value op1)) (var2 (get-bool-value op2)))
		(if op2 (cond ((string= "and" op) (and var1 var2))
					((string= "or" op) (or var1 var2))
					((string= "equal" op) (equal var1 var2)))
				(if (string= "not" op) (not var1)))) "true" "false"
	)
)

;;This function returnes the value of kw
(defun get-bool-value (op)
	(if (and (not (integerp op)) op (or (string= "true" op) (string= "false" op)))
	(string= "true" op))
)

;;This function adds to the last of the list
(defun add-to-last (lst a)
	(push a (cdr (last lst))) lst
)

;;This function tokenizes the line and returns the list of tokens.
(defun token-list (seq)
	(let ((lst (create-input-list seq)))
		(let ((token-lst 
			(if (string= (car lst) ";;") "COMMENT"  
				(map 'list #'(lambda (token) (tokenize token (get-token-lst))) lst)
			)
			))
			token-lst
		)
	)
)

;;This function remoesthe last element of the list
(defun remove-last(l)
    (reverse (cdr (reverse l)))
)

;;This function determines the operator token
(defun is-op (token)
	(or (string= "OP_PLUS" token)
		(string= "OP_MINUS" token)
		(string= "OP_DIV" token)
		(string= "OP_MULT"token)
		(string= "OP_DBLMULT" token)		
	)
)

;;This function removes the first k elements of the given list
(defun remove-first-k-elements (my_list k)
	(if (= k 0) my_list (remove-first-k-elements (cdr my_list) (- k 1)))
)

;;This function determines given input is EXPI2 or not
(defun is-EXPI2 (id-token)
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))  
		 
		
		(if (and (string= "OP_OP" foo) (string= "KW_IF" foo2))
			(let ((p1 nil) (k 2)) ;; "(", "if" -> k=2.
			(setq p1	;; ("if" EXPB EXPLISTI) 
			(and  (let ((expb (is-EXPB (remove-first-k-elements id-token k))))	
					(setq k (+ k (cadr expb)))(car expb)) ;; EXPB
				  (let ((explisti (is-EXPLISTI (remove-first-k-elements id-token k))))
					(setq k (+ k (cadr explisti))) (car explisti)) ;; EXPLISTI
				  (string= "OP_CP" (car (remove-first-k-elements id-token k))))) ;; ")"


			(setq k 2)
			(setq p2 ;; ("if" EXPB EXPLISTI EXPLISTI) 
			(and (let ((expb (is-EXPB (remove-first-k-elements id-token k))))	
					(setq k (+ k (cadr expb))) (car expb)) ;; EXPB
				  (let ((explisti (is-EXPLISTI (remove-first-k-elements id-token k))))
					(setq k (+ k (cadr explisti))) (car explisti)) ;; EXPLISTI
				  (let ((explisti (is-EXPLISTI (remove-first-k-elements id-token k))))
					(setq k (+ k (cadr explisti))) (car explisti)) ;; EXPLISTI
				  (string= "OP_CP" (car (remove-first-k-elements id-token k))))) ;; ")"
			(return-from is-EXPI2 (list (or p1 p2) (+ k 1))))
		)
		;; (set ID EXPI)
		(if (and (string= "OP_OP" foo) (string= "KW_SET" foo2))
			(let ((p nil) (k 3))
				(setq p
				(and 	(string= "IDENTIFIER" (car (remove-first-k-elements id-token (- k 1))))
						(let ((expi (is-EXPI (remove-first-k-elements id-token k))))
						(setq k (+ k (cadr expi))) (car expi))
					 (string= "OP_CP" (car (remove-first-k-elements id-token k)))))
				(return-from is-EXPI2 (list p (+ k 1))))
		)

		;; (list LISTVALUE)
		(if (and (string= "OP_OP" foo) (string= "KW_LIST" foo2))
			(let ((p nil) (k 2))
				(setq p
				(and (let ((listvaluep (is-LISTVALUE (remove-first-k-elements id-token k))))
						(setq k (+ k (cadr listvaluep))) (car listvaluep))
					 (string= "OP_CP" (car (remove-first-k-elements id-token k)))))
				(return-from is-EXPI2 (list p (+ k 1))))
		)
		(list nil k)
	)
)

;; EXPI -> (if EXPB EXPLISTI)
;; EXPI -> (if EXPB EXPLISTI EXPLISTI)
;; EXPI -> (list LISTVALUE)
;; EXPI -> (set ID EXPI)
(defun parse-EXPI2(name-token id-token stack)
	(let ((op-stack (car stack)) (val-stack (cadr stack)))
		(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))
			(if (and (string= "OP_OP" foo) (string= "KW_IF" foo2)) ;; (if EXPB EXPLISTI)  
				(let ((k 2) (bool nil))
					(let ((expb (parse-EXPB (remove-first-k-elements name-token k)
						(remove-first-k-elements id-token k) stack)))
						(setq stack (car expb))
						(setq k (+ k (cadr expb)))
                    )

					(let ((explisti (parse-EXPLISTI (remove-first-k-elements name-token k) 
						(remove-first-k-elements id-token k) stack)))
						(setq stack (car explisti))
						(setq k (+ k (cadr explisti)))
                    )

					(setq lst (caadr stack))
					(setq bool (cadadr stack))
					(setq bool (caddr (cadr stack)))
					(setq val-stack (cddadr stack))
					(setq stack (list (car stack) (cdr val-stack)))

					(if (string= "OP_CP" (car (remove-first-k-elements id-token k)))
						(let () (if (get-bool-value bool) (let () 
						(setq val-stack (cons lst (cddadr stack)))
						(setq stack (list (car stack) val-stack))
						(return-from parse-EXPI2 (list stack (+ k 1))))))
					)
					

					(let ((explisti (parse-EXPLISTI (remove-first-k-elements name-token k) 
                        (remove-first-k-elements id-token k) stack)))
                        (setq stack (car explisti))
                        (setq k (+ k (cadr explisti)))
                    )

					(setq lst2 (cadr stack))
					(setq stack (list (car stack) (cddadr stack)))
					(if (get-bool-value bool) (setq val-stack (cons lst (cddadr stack)))
						(setq val-stack (cons lst2 (cddadr stack)))
					)

					(setq stack (list (car stack) val-stack))
					(return-from parse-EXPI2 (list stack (+ k 1)))
                )
            )

			(if (and (string= "OP_OP" foo) (string= "KW_LIST" foo2))
				(let ((k 2)) ;; EXPI -> (list LISTVALUE)
					(return-from parse-EXPI2 (parse-LISTVALUE 
						(remove-first-k-elements name-token k) (remove-first-k-elements id-token k) stack))
                )
            )

			(if (and (string= "OP_OP" foo) (string= "KW_SET" foo2))
				(let ((k 2)) ;; EXPI -> (set id EXPI)
					(setq var (car (remove-first-k-elements name-token k)))
					(setq k (+ k 1))
					(let ((expi (parse-EXPI (remove-first-k-elements name-token k)
						(remove-first-k-elements id-token k) stack)))
						(setq stack (car expi))
						(setq k (+ k (cadr expi))))
					(setq val-stack (cadr stack))
					(setq value (car val-stack))
					(setf (gethash var *vars*) value)
					(setq stack (list (car stack) val-stack))
					(return-from parse-EXPI2 (list stack (+ k 1)))
                )
            )

			(list nil 0)
		)
	)
)
;; EXPI lookahead prediction.
(defun is-EXPB (id-token)
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))  
		;; (and, or, equal, not ..) 
		(if (string= "OP_OP" foo)
			(let ((p nil) (k 2)) ;; "(", "OP" -> k=2.

				(setq p (let ((expb (is-EXPB (remove-first-k-elements id-token k))))
						(setq k (+ k (cadr expb))) (car expb)))    ;; EXPB

				(if (not (string= "KW_NOT" foo2))	
					 (setq p (and p (let ((expb (is-EXPB (remove-first-k-elements id-token k))))
					 	(setq k (+ k (cadr expb ))) (car expb))))
				) ;; EXPB



				(if (string= "KW_EQUAL" foo2)
					(setq p (or p (let ((p1 nil) (j 2))
						(setq p1
						(and (let ((expi (is-EXPI (remove-first-k-elements id-token j))))
								(setq j (+ j (cadr expi))) (car expi))   ;; EXPI
							 (let ((expi (is-EXPI (remove-first-k-elements id-token j))))
							 	(setq j (+ j (cadr expi))) (car expi)))) ;; EXPI
						(if p1 (setq k j)) p1)))
				)

				(if (string= "KW_LESS" foo2)
					(setq p (or p (let ((p1 nil) (j 2))
						(setq p1
						(and (let ((expi (is-EXPI (remove-first-k-elements id-token j))))
								(setq j (+ j (cadr expi))) (car expi))   ;; EXPI
							 (let ((expi (is-EXPI (remove-first-k-elements id-token j))))
							 	(setq j (+ j (cadr expi))) (car expi)))) ;; EXPI
						(if p1 (setq k j)) p1)))
				)

				(setq p (and p (string= "OP_CP" (car (remove-first-k-elements id-token k)))))
				(return-from is-EXPB (list p (+ k 1)))
			)
				
		)

		;; Binary Value.
		(if (or (string= "KW_TRUE" foo) (string= "KW_FALSE" foo)) 
			(let ()
				(setq k 1) (return-from is-EXPB (list t k))))
		(list nil k)
	)
)

;; EXPB -> (and EXPB EXPB) |
;; 			(or EXPB EXPB) | 
;; 			    (not EXPB) |
;; 		 (equal EXPB EXPB) | 
;;		 (equal EXPI EXPI) | 
;;		 (less EXPI EXPI)  |
;;			   BinaryValue .
(defun parse-EXPB (name-token id-token stack)
	(let ((op-stack (car stack)) (val-stack (cadr stack)))
		(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))

			(if (string= "OP_OP" foo) ;; (and, equal, or, not EXPB EXPB)  
			(let ((k 2))
				(setq op-stack (cons (car name-token) op-stack)) ;; push '('.
				(setq op-stack (cons (cadr name-token) op-stack)) ;; push KW.
				(setq stack (list op-stack val-stack))
				

				;;(less EXPI EXPI)
				(if (string= "KW_LESS" foo2)
					(if (car (is-EXPI (remove-first-k-elements id-token k)))
						(let () (dotimes (i 2) 
						(let ((expi (parse-EXPI (remove-first-k-elements name-token k) 
							  (remove-first-k-elements id-token k) stack)))
							(setq stack (car expi))
							(setq k (+ k (cadr expi)))))

						(let ((op1 (caadr stack)) (op2 (cadadr stack)) (op (caar stack)))
						(setq stack (list (cdar stack) (cddadr stack)))
						(setq stack (list (cdar stack) (cons (perform-bool-operation op op1 op2) (cadr stack)))))
						(return-from parse-EXPB (list stack (+ k 1)))))
				
				)

				;; (equal EXPI EXPI)
				(if (string= "KW_EQUAL" foo2)
					(if (car (is-EXPI (remove-first-k-elements id-token k)))
						(let () (dotimes (i 2) 
						(let ((expi (parse-EXPI (remove-first-k-elements name-token k) 
							  (remove-first-k-elements id-token k) stack)))
							(setq stack (car expi))
							(setq k (+ k (cadr expi)))))

						(let ((op1 (caadr stack)) (op2 (cadadr stack)) (op (caar stack)))
						(setq stack (list (cdar stack) (cddadr stack)))
						(setq stack (list (cdar stack) (cons (perform-bool-operation op op1 op2) (cadr stack)))))
						(return-from parse-EXPB (list stack (+ k 1)))))
				)


				;; EXPB.
				(let ((expb (parse-EXPB (remove-first-k-elements name-token k) 
					  (remove-first-k-elements id-token k) stack)))
					(setq stack (car expb))
					(setq k (+ k (cadr expb))))

				;; EXPB.
				(if (not (string= "KW_NOT" foo2))
					(let ((expb (parse-EXPB (remove-first-k-elements name-token k) 
					  (remove-first-k-elements id-token k) stack)))

					(setq stack (car expb))
					(setq k (+ k (cadr expb)))

					;; evaluate and clean the stack.
					(let ((op1 (caadr stack)) (op2 (cadadr stack)) (op (caar stack)))
						(setq stack (list (cdar stack) (cddadr stack)))
						(setq stack (list (cdar stack) (cons (perform-bool-operation op op1 op2) (cadr stack))))
						))
					(let ((op1 (caadr stack)) (op2 (cadadr stack)) (op (caar stack)))
						(setq stack (list (cdar stack) (cddadr stack)))
						(setq stack (list (cdar stack) (cons (perform-bool-operation op op1) (cadr stack))))
						)
					)
				(return-from parse-EXPB (list stack (+ k 1)))))

			(if (or (string= "KW_TRUE" foo) (string= "KW_FALSE" foo))
				(let ()
					(setq val-stack (cons (car name-token) val-stack)) ;; push id.
					(setq stack (list op-stack val-stack))
					(setq k 1) (return-from parse-EXPB (list stack k))))))

			(list nil 0)
)

;; This function determines the given input is EXPLISTI or not
(defun is-EXPLISTI (id-token)
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))

		;; null
		(if (string= "KW_NIL" foo) (let ()
				(setq k 1) (return-from is-EXPLISTI (list t k)))
		)

		;; LISTVALUE
		(let ((listvaluep (is-LISTVALUE id-token)))
			(if (car listvaluep) (return-from is-EXPLISTI listvaluep))
		)


		(if (string= "OP_OP" foo) 
		;; (concat EXPLISTI EXPLISTI) 
		(let ()
		(if (and (string= "KW_CONCAT" foo2))
			(let ((p nil) (k 2)) ;; "(", "concat" -> k=2.
			(setq p	
			(and  (let ((explisti (is-EXPLISTI (remove-first-k-elements id-token k))))	
					(setq k (+ k (cadr explisti))) (car explisti)) ;; EXPLISTI
				  (let ((explisti (is-EXPLISTI (remove-first-k-elements id-token k))))
					(setq k (+ k (cadr explisti))) (car explisti)) ;; EXPLISTI
				  (string= "OP_CP" (car (remove-first-k-elements id-token k))))) ;; ")"
			(return-from is-EXPLISTI (list p (+ k 1))))
		)
			

			;; (append EXPI EXPLISTI)
			(if (and (string= "KW_APPEND" foo2))
				(let ((p nil) (k 2)) ;; "(", "append" -> k=2.	
				(setq p	
				(and  (let ((expi (is-EXPI (remove-first-k-elements id-token k))))	
						(setq k (+ k (cadr expi))) (car expi)) ;; EXPI
					  (let ((explisti (is-EXPLISTI (remove-first-k-elements id-token k))))
						(setq k (+ k (cadr explisti))) (car explisti)) ;; EXPLISTI
					  (string= "OP_CP" (car (remove-first-k-elements id-token k))))) ;; ")"
				(return-from is-EXPLISTI (list p (+ k 1))))
			))
		)

		(list nil k))
)

;; EXPLISTI -> (concat EXPLISTI EXPLISTI) | 
;; 				   (append EXPI EXPLISTI) | 
;; 								LISTVALUE | 
;; 									nil
(defun parse-EXPLISTI (name-token id-token stack)
	(let ((op-stack (car stack)) (val-stack (cadr stack)))
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))
		
		;; null
		(if (string= "KW_NIL" foo) (let ()
				(setq k 1) (setq val-stack (cons (car name-token) val-stack))
				(setq stack (list op-stack val-stack))
				(return-from parse-EXPLISTI (list stack k)))
		)

		(if (car (is-LISTVALUE id-token)) (return-from parse-EXPLISTI 
			(parse-LISTVALUE name-token id-token stack))
		)

		(if (string= "OP_OP" foo) 
		;; (concat EXPLISTI EXPLISTI) 
		(let ()
		(if (and (string= "KW_CONCAT" foo2))
			(let ((k 2)) ;; "(", "concat" -> k=2.


				(dotimes (i 2) ;; parse EXPLISTI
				(let ((explisti (parse-EXPLISTI (remove-first-k-elements name-token k)
					(remove-first-k-elements id-token k) stack)))

					(setq k (+ k (cadr explisti)))
					(setq stack (car explisti))))

			#| 
			(setq val-stack (cadr stack))
			(let ((val-stack1 (car val-stack)) (val-stack2 (cadr val-stack)) (r '()))
				(setq r (concatenate val-stack2 (cdr val-stack1)))
				(setq val-stack (cons r (cddr val-stack))))
			(setq stack (list op-stack val-stack))
			|# 

			(return-from parse-EXPLISTI (list stack (+ k 1))))
		)

		(if (and (string= "KW_APPEND" foo2))
			(let ((k 2)) ;; "(", "append" -> k=2.

			 ;; parse EXPI
			 (let ((expi (parse-EXPI (remove-first-k-elements name-token k) 
				(remove-first-k-elements id-token k) stack)))
				(setq k (+ k (cadr expi)))
				(setq stack (car expi)))


			;; parse EXPLIST
			(let ((explisti (parse-EXPLISTI (remove-first-k-elements name-token k) 
				(remove-first-k-elements id-token k) stack)))
				(setq k (+ k (cadr explisti)))
				(setq stack (car explisti)))
	
			(setq val-stack (cadr stack))

			(let ((val-stack1 (car val-stack)) (val (cadr val-stack)) (r '()))
				(setq r (add-to-last val-stack1 val))
				(setq val-stack (cons r (cddr val-stack))))
			(setq stack (list op-stack val-stack))
			(return-from parse-EXPLISTI (list stack (+ k 1))))

		)

		)

		))
	)

		(list nil 0)
)

;;This function determines input is list of values or not
(defun is-LISTVALUE (id-token)
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0)) 

		;; null
		(let () (if (string= "KW_NIL" foo) (let ()
				(setq k 1) (return-from is-LISTVALUE (list t k)))))

		(if (string= "OP_OP" foo) 
			(let ((k 1))

			;; ()
			(if (string= "OP_CP" foo2)
				(let ((k 2)) (return-from is-LISTVALUE (list t k))))

			;; VALUES
			(if  (and (let ((valuesp (is-VALUES (cdr id-token))))
				 (setq k (+ k (cadr valuesp)))(car valuesp))
				 (string= "OP_CP" (car (remove-first-k-elements id-token k))))
			(return-from is-LISTVALUE (list t (+ k 1)))))
		)

		(list nil k))
)

;; LISTVALUE -> (VALUES) | () | nil
(defun parse-LISTVALUE (name-token id-token stack)
	(let ((op-stack (car stack)) (val-stack (cadr stack)))
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))
		
		;; null
		(if (string= "KW_NIL" foo) (let ()
				(setq k 1) (setq val-stack (cons (car name-token) val-stack))
				(setq stack (list op-stack val-stack))
				(return-from parse-LISTVALUE (list stack k)))
		)


		(if (string= "OP_OP" foo) 
			(let ((k 1))

			;; ()
			(if (string= "OP_CP" foo2)
				(let ((k 2)) (setq val-stack (cons '(0) val-stack))
					(setq stack (list op-stack val-stack))
					(return-from parse-LISTVALUE (list stack k))))

			;; VALUES
			(if (car (is-VALUES (cdr id-token))) (let (valuesp '())
				(setq valuesp (parse-VALUES (cdr name-token) (cdr id-token) stack))
				(setq k (+ 2 (cadr valuesp)))
				(return-from parse-LISTVALUE (list (car valuesp) k)))))
		))

		(list nil 0))
)

;;This function determines input is list of values or not
(defun is-VALUES (id-token)
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))
		(if id-token (let ()

		;; VALUES IntegerValue | IntegerValue
		(let ((k 1)) (if (string= "VALUE" foo) 
			(let ((valuesp (is-VALUES (cdr id-token))))
			(if (car valuesp) (let () (setq k (+ k (cadr valuesp)))
				(return-from is-VALUES (list t k)))
				(return-from is-VALUES (list t 1))
			)))
		)


		(list nil k))
		)
	)
)

;; VALUES -> VALUES IntegerValue | IntegerValue
(defun parse-VALUES (name-token id-token stack)
	(let ((op-stack (car stack)) (val-stack (cadr stack)))
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0) (val-lst (car val-stack)))
		(if id-token (let ()
			(if (not (listp val-lst)) (setq val-lst '(0))) ;; val-lst is ready.

			(let ((k 1)) (if (string= "VALUE" foo)
				(let ()
				(setq val-lst (car val-stack))	

				;; 	liste degil ve 0 ise, direkt ekle ;; (= (car val-stack) 0)
				(if (and (not (listp (car val-stack))) t) 
					(setq val-stack (cons val-lst val-stack)))


				;; val-lst liste.
				(if (listp val-lst)	
				(setq val-lst (add-to-last val-lst (parse-integer (car name-token))))
				(setq val-lst (list (parse-integer (car name-token))))
				)

					
				(if (listp (car val-stack)) (setq val-stack (cons val-lst (cdr val-stack)))
				(setq val-stack (cons val-lst val-stack))
				)

				(setq stack (list op-stack val-stack))
				(let ()
					(if (car (is-VALUES (cdr id-token))) 
						(let ((valuesp (parse-VALUES (cdr name-token) 
						(cdr id-token) stack)))
						(setq k (+ k (cadr valuesp)))
						(return-from parse-VALUES (list (car valuesp) k)))))

				(return-from parse-VALUES (list stack k))))))
			)))

		(list nil 0)
) 

;; EXPI looks its ahead to predict
;; After peeking, returns token and its number or null and 0
(defun is-EXPI (id-token)
	(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))  
		 
		;; EXPI -> (OP EXPI EXPI) 
		(if (and (string= "OP_OP" foo) (is-op foo2))
			(let ((p nil) (k 2)) ;; "(", "OP" -> k=2.
			(setq p	
			(and  (let ((expi (is-EXPI (remove-first-k-elements id-token k))))	
					(setq k (+ k (cadr expi))) (car expi)) ;; EXPI
				  (let ((expi (is-EXPI (remove-first-k-elements id-token k))))
					(setq k (+ k (cadr expi))) (car expi)) ;; EXPI
				  (string= "OP_CP" (car (remove-first-k-elements id-token k))))) ;; ")"
			(return-from is-EXPI (list p (+ k 1))))
		)
		
		;; EXPI -> ID VALUE
		(if (or (string= "IDENTIFIER" foo) (string= "VALUE" foo))
			(let ()
				(setq k 1) (return-from is-EXPI (list t k)))
		)

		;; EXPI -> (ID EXPLISTI)
		(if (and (string= "OP_OP" foo) (string= "IDENTIFIER" foo2))
			(let ((p nil) (k 2))
				(setq p
				(and (let ((expi (is-EXPLISTI (remove-first-k-elements id-token k))))
						(setq k (+ k (cadr expi))) (car expi))
					 (string= "OP_CP" (car (remove-first-k-elements id-token k)))))
				(return-from is-EXPI (list p (+ k 1))))
		)

		(list nil k))
)

;; EXPI -> (+ EXPI EXPI) |
;; 		   (- EXPI EXPI) | 
;; 		   (* EXPI EXPI) |
;; 		   (/ EXPI EXPI) | 
;;		   (** EXPI EXPI)|
;; 					  ID | 
;; 		    IntegerValue | 
;; 			(ID EXPLISTI).
(defun parse-EXPI (name-token id-token stack)
	(let ((op-stack (car stack)) (val-stack (cadr stack)))
		(let ((foo (car id-token)) (foo2 (cadr id-token)) (k 0))
			(if (string= "OP_OP" foo) ;; ("OP" EXPI EXPI)  
				(let ((k 2))
					(setq op-stack (cons (car name-token) op-stack)) ;; push '('.
					(setq op-stack (cons (cadr name-token) op-stack)) ;; push 'op' or id.
					(setq stack (list op-stack val-stack))

					(if (is-op foo2) ;; push 2x EXPI
					(dotimes (i 2) 
					(let ((expi (parse-EXPI (remove-first-k-elements name-token k) 
						  (remove-first-k-elements id-token k) stack)))
						(setq stack (car expi))
						(setq k (+ k (cadr expi)))))
					)
					(if (string= "IDENTIFIER" foo2) ;; push EXPLISTI
						(let ((expi (parse-EXPLISTI (remove-first-k-elements name-token k) 
						  (remove-first-k-elements id-token k) stack)))
						(setq stack (car expi))
						(setq k (+ k (cadr expi))))
					)

					;; evaluate and clean the stack.
					(let ((op1 (caadr stack)) (op2 (cadadr stack)) (op (caar stack)))
						(setq stack (list (cdar stack) (cddadr stack)))
						(setq stack (list (cdar stack) (cons (perform-math-operation op2 op1 op) (cadr stack))))
						)

					(return-from parse-EXPI (list stack (+ k 1))))
			)

			;; ID
			(if (string= "IDENTIFIER" foo) 
				(let ((value nil))
					(if (gethash (car name-token) *vars*) (setq value 
						(gethash (car name-token) *vars*))(print "Error, no symbol found in symbol table!"))
					(setq val-stack (cons value val-stack)) ;; push id.
					(setq stack (list op-stack val-stack))
					(setq k 1) (return-from parse-EXPI (list stack k)))
			)

			;; VALUE
			(if (string= "VALUE" foo)
				(let ()
					(setq val-stack (cons (parse-integer (car name-token)) val-stack)) ;; push id.
					(setq stack (list op-stack val-stack))
					(setq k 1) (return-from parse-EXPI (list stack k)))
			)

			(list nil 0)))
)

;;INPUT -> EXPI | EXPLISTI | EXPB | COMMENT | EXIT
(defun parse-INPUT (name_token id_token)

	(let ((stack (list '(0) '(0))) (k 0)) ;; init op-stack and val-stack.
    ;;Firstly checks wheter input is expi or not, then if it is expi, parses the expi
        (cond ((car (is-EXPI id_token))
            (let ((expi (parse-EXPI name_token id_token stack))) 
                (setq stack (car expi))
                (setq k (cadr (is-EXPI id_token)))))
            ((car (is-EXPB id_token))

            ;;checks whether input is expb or not
            (let ((expb (parse-EXPB name_token id_token stack))) 
                (setq stack (car expb))
                (setq k (cadr (is-EXPB id_token)))))
            ((car (is-EXPLISTI id_token))

            ;;checks wheter input is explisti or not
            (let ((explisti (parse-EXPLISTI name_token id_token stack))) 
            (setq stack (car explisti))
            (setq k (cadr (is-EXPLISTI id_token)))))
            ((car (is-EXPI2 id_token))

            ;;checks wheter input is expı2 or not, expı2 means that 
            ;; EXPI -> (if EXPB EXPLISTI)
            ;; EXPI -> (if EXPB EXPLISTI EXPLISTI)
            ;; EXPI -> (list LISTVALUE)
            ;; EXPI -> (set ID EXPI) (different from above all) these are seperated because these returns a list

            (let ((expi2 (parse-EXPI2 name_token id_token stack))) 
            (setq stack (car expi2))
            (setq k (cadr (is-EXPI2 id_token)))))
                (t (let () (princ "SYNTAX_ERROR Expression not recognized.") 
                    (return-from parse-INPUT)))
        )

        ;;there is an syntax error
        (if (/= (list-length id_token) k) 
            (let () (princ "SYNTAX_ERROR Expression not recognized.") 
            (return-from parse-INPUT))
        )

        (terpri)
        (princ "SYNTAX OK.") (terpri)
        (princ "Result: ")	
        (setq val-stack (cadr stack))	
        (princ (caadr stack))
	)
) 

;; START -> INPUT
(defun parse-START (seq)
	(let ((name_token (create-input-list seq)) (id_token (token-list seq)))
		(parse-INPUT name_token id_token)
	)
)

;;takes input from file read file
(defun take-from-file (filename)
	(defvar counter 1)
    (let ((input_file (open filename :if-does-not-exist nil)))          ;;open the file
        (when input_file
            (loop for line = (read-line input_file nil)         ;;read the line from input file
            while line do (write counter) (parse-START line) (setq counter (+ counter 1)) (terpri) )                    ;;parse the line into tokens
            (close input_file)
        )
    )    
)
;;takes input from terminal
(defun take-from-terminal ()
    (loop
        (setq read_the_line (read-line))             ;;read the line
        (when (equal "(exit)" read_the_line) (return)) ;;if (exit) is entered
        (setq control (parse-START read_the_line))    ;;parse the line into tokens
        (terpri)
        (when (= control -1) (return))              ;;exit if we are gonna terminate
    )  
)

;;takes one or zero input, depend on the input decides read input from terminal or file
(defun gppinterpreter (&optional filename)
    (if (equal filename nil) (take-from-terminal) (take-from-file filename))
)
;;removes the g++ from input
(defun remove_chars(command)
    (setq command2 (string-trim "g++ " command))
    (return-from remove_chars command2)
)
(defun main ()
    (write "Type g++ or type g++ filename.txt to read input")
    (terpri)
    (setq command (read-line))
    (if (equal "g++" command)(gppinterpreter) (gppinterpreter (remove_chars command)))
)

(load "gpp_lexer.lisp")
(main)