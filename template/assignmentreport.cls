\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{assignmentreport}[2023/10/22 UC San Diego CSE 221]
\LoadClass{article}

\RequirePackage{colortbl}
\RequirePackage{xcolor}
\RequirePackage{hyperref}

\AtBeginDocument{
    \hypersetup{
        citecolor=blue,
        pdftitle=aaa,
        pdfauthor={\@author},
    }
}

% renew \section to center the title
\renewcommand\section{\@startsection{section}{1}{\z@}%
                                    {-3.5ex \@plus -1ex \@minus -.2ex}%
                                    {2.3ex \@plus.2ex}%
                                    {{\vspace{1cm}}\centering\bf\bfseries}}
\renewcommand\subsection{\@startsection{subsection}{2}{\z@}%
                                    {-3.25ex\@plus -1ex \@minus -.2ex}%
                                    {1.5ex \@plus .2ex}%
                                    {{\vspace{0.5cm}}\centering\bfseries}}
\renewcommand\subsubsection{\@startsection{subsubsection}{3}{\z@}%
                                    {-3.25ex\@plus -1ex \@minus -.2ex}%
                                    {1.5ex \@plus .2ex}%
                                    {{\vspace{0.5cm}}\centering\bfseries}}
\newcommand{\newabstract}{{\bf Abstract: }}
                            