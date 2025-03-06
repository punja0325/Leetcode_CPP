-- 檢測是否運行於 VSCode
if vim.g.vscode then
    -- **設定 Leader 鍵為空格**
    vim.g.mapleader = " "
    vim.g.maplocalleader = " "
  
    -- VSCode-Neovim 專用設定
    vim.opt.clipboard = "unnamedplus" -- 啟用系統剪貼簿
    vim.opt.number = true             -- 顯示行號
    vim.opt.relativenumber = true     -- 顯示相對行號
    vim.opt.cursorline = true         -- 高亮當前行
    vim.opt.tabstop = 4               -- Tab 顯示為 4 個空格
    vim.opt.shiftwidth = 4            -- 縮進時使用 4 個空格
    vim.opt.expandtab = true          -- Tab 替換為空格
    vim.opt.ignorecase = true         -- 忽略大小寫搜索
    vim.opt.smartcase = true          -- 但如果有大寫字母，則區分大小寫
  
    -- **鍵位映射**
    local map = vim.api.nvim_set_keymap
    local opts = { noremap = true, silent = true }
  
    -- **模式切換快捷鍵**
    map("i", "jj", "<ESC>", opts)  -- 在插入模式下，輸入 jj 退回普通模式
    map("i", "jk", "<ESC>", opts)  -- 或者用 jk 也可以
  
    -- **基本快捷鍵**
    map("n", "<C-s>", ":w<CR>", opts)                -- Ctrl + S 保存
    map("n", "<C-q>", ":q<CR>", opts)                -- Ctrl + Q 退出
    map("n", "<C-a>", "ggVG", opts)                  -- Ctrl + A 全選
    map("n", "<C-d>", "<C-d>zz", opts)               -- Ctrl + D 向下滾動一半
    map("n", "<C-u>", "<C-u>zz", opts)               -- Ctrl + U 向上滾動一半
    map("n", "<Leader>y", '"+y', opts)               -- 複製到系統剪貼簿
    map("n", "<Leader>p", '"+p', opts)               -- 從系統剪貼簿貼上
    map("n", "<Leader>h", ":nohlsearch<CR>", opts)   -- 取消搜索高亮
  
    -- **窗口管理**
    map("n", "<C-h>", "<C-w>h", opts)                -- 切換到左側窗口
    map("n", "<C-l>", "<C-w>l", opts)                -- 切換到右側窗口
    map("n", "<C-j>", "<C-w>j", opts)                -- 切換到下方窗口
    map("n", "<C-k>", "<C-w>k", opts)                -- 切換到上方窗口
    map("n", "<C-w>v", ":vsplit<CR>", opts)          -- 垂直分割窗口
    map("n", "<C-w>s", ":split<CR>", opts)           -- 水平分割窗口
    map("n", "<C-w>q", ":close<CR>", opts)           -- 關閉當前窗口
  
    -- **移動行**
    map("n", "<A-j>", ":m .+1<CR>==", opts)          -- Alt + j 移動當前行到下一行
    map("n", "<A-k>", ":m .-2<CR>==", opts)          -- Alt + k 移動當前行到上一行
    map("v", "<A-j>", ":m '>+1<CR>gv=gv", opts)      -- Alt + j 選中移動
    map("v", "<A-k>", ":m '<-2<CR>gv=gv", opts)      -- Alt + k 選中移動
  
    -- **LSP (Clangd) 相關快捷鍵**
    map("n", "gd", "<cmd>lua vim.lsp.buf.definition()<CR>", opts)      -- 跳轉到定義
    map("n", "gD", "<cmd>lua vim.lsp.buf.declaration()<CR>", opts)     -- 跳轉到聲明
    map("n", "gi", "<cmd>lua vim.lsp.buf.implementation()<CR>", opts)  -- 跳轉到實作
    map("n", "gr", "<cmd>lua vim.lsp.buf.references()<CR>", opts)      -- 查找引用
    map("n", "K", "<cmd>lua vim.lsp.buf.hover()<CR>", opts)            -- 顯示函數說明
    map("n", "<Leader>rn", "<cmd>lua vim.lsp.buf.rename()<CR>", opts)  -- 變數重命名
    map("n", "<Leader>ca", "<cmd>lua vim.lsp.buf.code_action()<CR>", opts) -- 代碼修復
    map("n", "[d", "<cmd>lua vim.diagnostic.goto_prev()<CR>", opts)    -- 跳轉到前一個診斷
    map("n", "]d", "<cmd>lua vim.diagnostic.goto_next()<CR>", opts)    -- 跳轉到下一個診斷
    map("n", "<Leader>e", "<cmd>lua vim.diagnostic.open_float()<CR>", opts) -- 顯示診斷資訊
    map("n", "<Leader>q", "<cmd>lua vim.diagnostic.setloclist()<CR>", opts) -- 記錄診斷列表
    map("n", "<Leader>f", "<cmd>lua vim.lsp.buf.format()<CR>", opts)   -- 格式化代碼
  
    -- **分屏內滾動**
    map("n", "<C-Down>", "<C-w>j", opts)
    map("n", "<C-Up>", "<C-w>k", opts)
    map("n", "<C-Left>", "<C-w>h", opts)
    map("n", "<C-Right>", "<C-w>l", opts)
  
    -- **gd 視窗切換快捷鍵**
    map("n", "<C-w>w", "<C-w>w", opts)  -- 跳轉到 LSP 定義窗口
    map("n", "<Leader>n", "<cmd>cnext<CR>", opts) -- 跳到 quickfix 下一個
    map("n", "<Leader>p", "<cmd>cprev<CR>", opts) -- 跳到 quickfix 上一個
    map("n", "<Leader>q", "<cmd>cclose<CR>", opts) -- 關閉 quickfix 視窗
  
    -- **自動命令**
    vim.cmd([[
      augroup MyAutoCmd
        autocmd!
        autocmd BufWritePre * :%s/\s\+$//e  " 保存時自動刪除行尾空格
      augroup END
    ]])
     
   --  -- **插件管理 (在 VSCode 環境下部分插件可能無法運行)**
   --  require('packer').startup(function()
   --    use 'wbthomason/packer.nvim'       -- 插件管理器
   --    use 'neovim/nvim-lspconfig'        -- LSP 支援
   --    use 'hrsh7th/nvim-cmp'             -- 自動補全
   --    use 'hrsh7th/cmp-nvim-lsp'         -- LSP 補全
   --    use 'L3MON4D3/LuaSnip'             -- 代碼片段
   --    use 'nvim-treesitter/nvim-treesitter'  -- 語法高亮
   --  end)
  
    -- **LSP 設定 (Clangd)**
    local lspconfig = require('lspconfig')
    lspconfig.clangd.setup {}
  
  else
    -- 普通 Neovim 設定
    print("Running in standalone Neovim")
  
  -- <leader> key
  vim.g.mapleader = ' '
  
  -- exit insert mode
  vim.keymap.set('i', 'jj', '<ESC>')
  
  -- move line up/down
  vim.keymap.set({'n', 'v'}, 'J', ':m .+1<CR>==')
  vim.keymap.set({'n', 'v'}, 'K', ':m .-2<CR>==')
  
  -- move cursor
  vim.keymap.set({'n', 'v'}, 'k', 'gk')
  vim.keymap.set({'n', 'v'}, 'j', 'gj')
  
  -- move to beginning/end of line
  vim.keymap.set({'n', 'v'}, 'H', '^')
  vim.keymap.set({'n', 'v'}, 'L', '$')
  
  -- paste without overwriting
  vim.keymap.set({'n', 'v'}, 'p', 'P')
  
  -- save and quit
  vim.keymap.set('n', '<leader>s', ':w<CR>')
  vim.keymap.set('n', '<leader>q', ':q<CR>')
  
  -- redo
  vim.keymap.set('n', 'U', '<C-r>')
  
  -- clear search highlight
  vim.keymap.set('n', '<leader>h', ':noh<CR>')
  
  -- sync with system clipboard
  vim.opt.clipboard = 'unnamedplus'
  
  --ignore case when searching
  vim.opt.ignorecase = true
  
  -- disable "ignorecase" when search pattern contains upper case characters
  vim.opt.smartcase = true
  
  
  end
  