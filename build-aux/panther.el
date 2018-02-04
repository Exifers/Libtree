;;; panther.el --- Mode for editing programs written in Panther,
;;; Appel's original (object-less) Tiger language.

;; Copyright (C) 2001, 2007  Edward O'Connor <ted@oconnor.cx>

;; Author: Edward O'Connor <ted@oconnor.cx>
;; Keywords: languages
;; Maintainers :
;;     Jerome Bana <bana_j@epita.fr>
;;     Benoit Perrot <perrot_b@epita.fr>
;;     Roland Levillain <roland@lrde.epita.fr>

;; This file is free software; you can redistribute it and/or modify
;; it under the terms of version 2 of the GNU General Public License
;; as published by the Free Software Foundation.
;; This file is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; I'm sure you already have many copies of the GPL on your machine.
;; If you're using GNU Emacs, try typing C-h C-c to bring it up. If
;; you're using XEmacs, C-h C-l does this.

;;; Commentary:
;; This mode only supports font-locking, unfortunately. If you'd like
;; to add functionality, please do so! :) You'll want to add something
;; like this to your .emacs file:

;; (autoload 'panther-mode "panther" "Load panther-mode" t)
;; (add-to-list 'auto-mode-alist '("\\.pa[nh]$" . panther-mode))

;;; History:
;; In the Compilers class I took in college[0], we used Appel's
;; _Modern Compiler Implementation in Java_ text[1], in which he uses
;; the Tiger language. After a few weeks of our final project (which
;; was to write a Tiger compiler), I got sick of looking at
;; #c0c0c0-on-black Tiger text, and decided to hack up (at least) some
;; font-lock support for the language. Hence this file. I would have
;; added indenting stuff too, but the term ended and I graduated. :)
;; If you add functionality or whatever, please send me the changes;
;; I'll gladly maintain the code base or whatever. The latest version
;; can be found here: <URL:http://oconnor.cx/elisp/tiger.el>
;;
;;                                                              -- Ted
;;
;; 0. <URL:http://www.rose-hulman.edu/>
;; 1. <URL:http://www.cs.princeton.edu/~appel/modern/>


;;; Declare Panther mode.
(defgroup panther nil
  "Panther code editing commands for Emacs."
  :prefix "panther-"
  :group 'languages)

(defcustom panther-mode-hook nil
  "*Hook called by `panther-mode'."
  :type 'hook
  :group 'panther)


;;; Define Panther syntax table.
(defvar panther-mode-syntax-table nil
  "Syntax table used in Panther mode.")
(when (not panther-mode-syntax-table)
  (setq panther-mode-syntax-table (make-syntax-table))
  ;; Declare the underscore character '_' as being a valid part of a word.
  (modify-syntax-entry ?_ "w" panther-mode-syntax-table)
  ;; Comment (n for nested works only with emacs-21)
  (modify-syntax-entry ?/   ". 14n" panther-mode-syntax-table)
  (modify-syntax-entry ?*   ". 23" panther-mode-syntax-table)
  )

;;; Highlight Syntax.
(defconst panther-font-lock-keywords
  `(
    ;; Panther keywords:
    ("\\<\\(array\\|break\\|do\\|e\\(?:lse\\|nd\\)\\|f\\(?:or\\|unction\\)\\|i\\(?:f\\|mport\\|n\\)\\|let\\|nil\\|of\\|primitive\\|t\\(?:hen\\|o\\|ype\\)\\|var\\|while\\)\\>"
     (1 font-lock-keyword-face))

    ;; Reserved keywords (only valid in Leopard):
    ("\\<\\(class\\|extends\\|method\\|new\\)\\>"
     (1 font-lock-warning-face))

    ;; Reserved identifiers:
    ("\\<\\(_\\w*\\)\\>"
     (1 font-lock-warning-face))

    ;; Variable declarations:
    ("\\<var\\s +\\([a-zA-Z]\\w*\\)"
     (1 font-lock-variable-name-face))
    ("\\<\\([a-zA-Z]\\w*\\)\\s *:\\s *\\([a-zA-Z]\\w*\\)"
     (1 font-lock-variable-name-face)
     (2 font-lock-type-face))

    ;; Type declarations:
    ("\\<type\\s +\\([a-zA-Z]\\w*\\)\\>"
     (1 font-lock-type-face))
    ;; Builtin types:
    ("\\<\\(boolean\\|int\\|string\\)\\>"
     (1 font-lock-type-face))
    ;; _t and _type:
    ("\\<\\([a-zA-Z]\\w*_t\\(ype\\)?\\)\\>"
     (1 font-lock-type-face))

    ;; Function declarations:
    ("\\<function\\s +\\([a-zA-Z]\\w*\\)\\>"
     (1 font-lock-function-name-face))
    (":\\s *\\([a-zA-Z]\\w*\\)\\>"
     (1 font-lock-type-face))
    ;; Builtin functions:
    ("\\<\\(c\\(?:hr\\|oncat\\)\\|exit\\|flush\\|getchar\\|not\\|ord\\|print\\(?:_err\\|_int\\)?\\|s\\(?:ize\\|ubstring\\|tr\\(?:cmp\\|eq\\)\\)\\)\\>"
     (1 font-lock-builtin-face))
    )

  "Expressions to highlight in Panther modes.")

;;; Indent Panther code.
(defvar panther-indent 2
  "Indentation of Panther statements.")

(defun panther-search-block-backward (re re-start re-end)
  "Search backward for the opening of a code block."

  (setq found-p t)
  (let ((depth 1) (comment-level 0))

    (setq re (concat re "\\|/\\*\\|\\*/"))
    (while (< 0 depth)
      (if (not (re-search-backward re nil t)) (setq depth 0
						    comment-level -1
						    found-p nil))
      (cond
       ;; nested comment
       ((looking-at "/\\*") (setq comment-level (1+ comment-level)))
       ((looking-at "\\*/") (setq comment-level (1- comment-level)))
       ;; sentry
       ((< 0 comment-level) (setq depth 0))
       ;;
       ((= 0 comment-level)
	(cond
	 ((looking-at re-start) (setq depth (1+ depth)))
	 ((looking-at re-end) (setq depth (1- depth)))
	 ((= depth 1) (setq depth 0))
	 ))
       )
      )
    )
  found-p
  )

(defun panther-block-indentation ()
  "Return block indentation."

  (setq indent-inc 0)
  (let
      ((re "") (re-start "") (re-end ""))
    (cond
     ((looking-at "\\s *end\\>")
      (setq re "\\<\\(in\\|end\\)\\>"
	    re-start "\\<end\\>" re-end "\\<in\\>"))
     ((looking-at "\\s *in\\>")
      (setq re "\\<\\(let\\|in\\)\\>"
	    re-start "\\<in\\>" re-end "\\<let\\>"))
     ((looking-at "\\s *then\\>")
      (setq re "\\<\\(if\\|then\\)\\>"
	    re-start "\\<then\\>" re-end "\\<if\\>"))
     ((looking-at "\\s *else\\>")
      (setq re "\\<\\(then\\|else\\)\\>"
	    re-start "\\<else\\>" re-end "\\<then\\>"))
     ((looking-at "\\s *\\(var\\|type\\|function\\)\\>")
      (setq re "\\<\\(let\\|end\\)\\>"
	    re-start "\\<end\\>" re-end "\\<let\\>"
	    indent-inc panther-indent))

     ((looking-at "\\s *[])}]")
      (setq re "[][(){}]"
	    re-start "[])}]" re-end "[[({]"))
     ;; default
     (t
      (setq re "\\<\\(let\\|in\\|end\\|if\\|then\\|else\\|do\\|function\\|type\\)\\>\\|[][(){};]"
	    re-start "\\<end\\>\\|[])}]" re-end "\\<let\\>\\|[[({]"
	    indent-inc panther-indent)
      )
     )

    (if (not (panther-search-block-backward re re-start re-end))
	(setq indent-inc 0))
    )

  (if (looking-at ";")
      (panther-search-block-backward "\\<\\(let\\|in\\|end\\|if\\|then\\)\\>\\|[][(){}]"
				   "[])}]\\|then\\|end"
				   "[[({]\\|if\\|let"))

  (cond
   ;; handle opening parenthesis
   ((looking-at "[[(]")
    (+ (current-column)
       (if (not (looking-at "[[(]\\s *$"))
	   (min 1 indent-inc)
	 indent-inc)))
   ;; handle "then" single on line
   ((looking-at "then") (+ (current-indentation) indent-inc))
   ;; default
   (t (+ (current-column) indent-inc))
   )

  )


(defun panther-indent-line ()
  "Indent current line as Panther code."
  (interactive)

  (if (bobp)
      ;; Do not indent first line
      (indent-line-to 0)

    ;;;
    (if nil
	(progn
	  (beginning-of-line)
	  (panther-block-indentation))
    ;;;

    (let ((indent-level 0)
	  (move-to-indentation-p (<= (current-column)
				     (current-indentation))))
      (save-excursion
	(save-excursion
	  (beginning-of-line)
	  (setq indent-level (panther-block-indentation)))
	(indent-line-to indent-level)
	)
      (if move-to-indentation-p (back-to-indentation))
      )

    ;;;
    )
    ;;;

    )

  )



;(defun panther-indent-region (start end)
;  "From start to end, indent each line."
;  )


;;; Panther mode entry function.
(defun panther-mode ()
  "Major mode for editing Panther programs.
The following keys are bound:
\\{panther-mode-map}"
  (interactive)

  ;; Set up local variables
  (kill-all-local-variables)
  (make-local-variable 'font-lock-defaults)
  (make-local-variable 'comment-start)
  (make-local-variable 'comment-end)
  (make-local-variable 'indent-line-function)
  ;;
  (set-syntax-table panther-mode-syntax-table)
  (setq major-mode		'panther-mode
	mode-name		"Panther"
	font-lock-defaults	'(panther-font-lock-keywords)
	comment-start		"/*"
	comment-end		"*/"
	indent-line-function	'panther-indent-line
	)

  (setq panther-mode-map (make-sparse-keymap))
  (use-local-map panther-mode-map)

  ;; Run the Panther mode hook
  (run-hooks 'panther-mode-hook))

(provide 'panther)

;;; panther.el ends here
