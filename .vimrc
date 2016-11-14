set nu
syntax on
set hlsearch
set foldenable
set foldmethod=manual
set background=dark
"colorscheme evening
"colorscheme darkbule
"colorscheme peaksea
set completeopt=preview,menu
set makeprg=g++\-Wall\\%
set autowrite
set cursorline
set autoindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set number
set enc=utf-8
" lianxiang
set dictionary +=/usr/include
" 为C程序提供自动缩进
set smartindent 
"代码补全
set completeopt=preview,menu 
"自动补全
:inoremap ( ()<ESC>i 
:inoremap ) <c-r>=ClosePair(')')<CR> 
:inoremap { {<CR>}<ESC>O 
:inoremap } <c-r>=ClosePair('}')<CR> 
:inoremap [ []<ESC>i 
:inoremap ] <c-r>=ClosePair(']')<CR> 
:inoremap " ""<ESC>i 
:inoremap " <c-r>=ClosePair('"')<CR> 
" :inoremap ' ''<ESC>i 
" :inoremap ' <c-r>=ClosePair('\'')<CR> 
function! ClosePair(char) 
if getline('.')[col('.')-1] == a:char 
return "\<Right>" 
else 
return a:char 
endif 
endfunction 
filetype plugin indent on 
"打开文件类型检测, 加了这句才可以用智能补全
set completeopt=longest,menu 
