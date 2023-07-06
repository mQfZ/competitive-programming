-- See: https://github.com/mQfZ/dotfiles/tree/master/nvim for more info about
-- configuration.
local file_directory = vim.fn.expand('~/proj/cp')

require('luasnip.loaders.from_vscode').load_standalone({
    path = file_directory .. '/.vscode/cp.code-snippets'
})

local telescope_tasks = require('config.ext.telescope-tasks')

local function current_directory()
    return vim.fn.expand('%:p:h')
end

local function current_file()
    return vim.fn.expand('%:p')
end

local function create_terminal(command)
    if vim.env.TMUX then
        local job = vim.fn.jobstart(
            'tmux split-window -hf "' .. command .. ';'
         .. 'echo -e \'\nPress [ENTER] to terminate program.\';'
         .. 'read"', {
            cwd = file_directory
        })
    else
        error('tmux is not running')
    end
    --  vim.api.nvim_command('tmux split-window "' .. command .. '"')
    -- local terminal = Terminal:new({
    --     cmd = command,
    --     close_on_exit = false,
    --     clear_env = false,
    --     auto_scroll = true,
    --     on_open = function(term)
    --         vim.schedule(function()
    --             vim.cmd('startinsert!')
    --         end)
    --     end
    -- })
    -- terminal:toggle()
end


vim.env.PYTHONPATH = (vim.env.PYTHONPATH and vim.env.PYTHONPATH .. ':' or '')
                  .. vim.fn.expand(current_directory())

vim.filetype.add({
    extension = {
        ['in'] = 'text',
        ['out'] = 'text'
    }
})

vim.keymap.set('n', '<leader>y', [[<cmd>%y+<CR>]], { noremap = true })

script = 'python3 -m cphelper '

rules = {
    { value = 'cpp-debug', description = 'C++ Debug' },
    { value = 'cpp', description = 'C++' },
    { value = 'python', description = 'Python' },
    { value = 'cppheader-debug', description = 'C++ Header Debug' },
    { value = 'cppheader', description = 'C++ Header' },
}

templates = {
    { value = 'debug', description = 'Includes debug functionality' },
    { value = 'empty', description = 'Empty file' },
    { value = 'minimal', description = 'Minimal boilerplate code' },
    { value = 'usaco', description = 'USACO input/output + minimal' },
}

telescope_tasks.extend_inputs({
    main_file_rule = {
        name = 'Main File Rule',
        type = 'pick',
        description = 'Rule to run main file',
        choices = rules,
    },
    correct_file_rule = {
        name = 'Correct File Rule',
        type = 'pick',
        description = 'Rule to run correct (brute force) file',
        choices = rules,
    },
    generator_file_rule = {
        name = 'Generator File Rule',
        type = 'pick',
        description = 'Rule to run test case generator file',
        choices = rules,
    },
    correct_file = {
        name = 'Correct File',
        type = 'prompt',
        description = 'Relative path of the correct (brute force) file',
    },
    generator_file = {
        name = 'Generator File',
        type = 'prompt',
        description = 'Relative path of the test case generator file',
    },
    input_times = {
        name = 'Input Times',
        type = 'prompt',
        description = 'Number of times to run file with user input',
        default = '1'
    },
    new_files_rule = {
        name = 'New Files Rule',
        type = 'pick',
        description = 'Rule to generate new files with',
        choices = rules,
    },
    template = {
        name = 'Template',
        type = 'pick',
        description = 'Template to generate file(s) with',
        choices = templates,
    },
    new_file = {
        name = 'New File(s)',
        type = 'prompt',
        description = 'Relative path(s) of the new file(s) to be generated',
        default = 'main.cpp',
    },
    io_path = {
        name = 'Input/Output Path(s)',
        type = 'prompt',
        description = 'Relative path stem(s) of input/output file stems',
        default = '1',
    },
    contest_path = {
        name = 'Contest Path',
        type = 'prompt',
        description = 'Absolute path of contest directory (from root)',
    },
    task_paths = {
        name = 'Task Paths',
        type = 'prompt',
        description = 'Name of problems to generate',
    },
})

run_tasks = {
    compile = {
        name = 'Compile',
        description = 'Compile (if possible).',
        inputs = {  },
        command = function(input)
            cmd = script  .. ' compile'
               .. ' -mf ' .. current_file()
            create_terminal(cmd)
        end
    },
    compile_rule = {
        name = 'Compile Rule',
        description = 'Compile (if possible) with a rule.',
        mapping = '<leader>rm',
        inputs = { 'main_file_rule' },
        command = function(input)
            cmd = script  .. ' compile'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
            create_terminal(cmd)
        end
    },
    input = {
        name = 'Input',
        description = 'Run with user input.',
        inputs = {  },
        command = function(input)
            cmd = script  .. ' input'
               .. ' -mf ' .. current_file()
            create_terminal(cmd)
        end
    },
    input_rule = {
        name = 'Input Rule',
        description = 'Run with user input with a rule.',
        inputs = { 'main_file_rule' },
        command = function(input)
            cmd = script  .. ' input'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
            create_terminal(cmd)
        end
    },
    input_times = {
        name = 'Input Times',
        description = 'Run with user input X times.',
        mapping = '<leader>ri',
        inputs = { 'input_times' },
        command = function(input)
            cmd = script  .. ' input'
               .. ' -mf ' .. current_file()
               .. ' -t '  .. input.input_times
            create_terminal(cmd)
        end
    },
    input_rule_times = {
        name = 'Input Rule Times',
        description = 'Run with user input with a rule X times.',
        inputs = { 'main_file_rule', 'input_times' },
        command = function(input)
            cmd = script  .. ' input'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
               .. ' -t '  .. input.input_times
            create_terminal(cmd)
        end
    },
    run = {
        name = 'Run',
        description = 'Run against testcases.',
        inputs = {  },
        mapping = '<leader>rn',
        command = function(input)
            cmd = script  .. ' run'
               .. ' -mf ' .. current_file()
            create_terminal(cmd)
        end
    },
    run_rule = {
        name = 'Run Rule',
        description = 'Run against testcases with a rule.',
        inputs = { 'main_file_rule' },
        command = function(input)
            cmd = script  .. ' run'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
            create_terminal(cmd)
        end
    },
    check = {
        name = 'Check',
        description = 'Check against testcases.',
        mapping = '<leader>rc',
        inputs = {  },
        command = function(input)
            cmd = script  .. ' check'
               .. ' -mf ' .. current_file()
            create_terminal(cmd)
        end
    },
    check_rule = {
        name = 'Check Rule',
        description = 'Check against testcases with a rule.',
        inputs = { 'main_file_rule' },
        command = function(input)
            cmd = script  .. ' check'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
            create_terminal(cmd)
        end
    },
    counter_test_case = {
        name = 'Counter Test Case',
        description = 'Generate counter testcase.',
        inputs = {  },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
        end
    },
    counter_test_case_open = {
        name = 'Counter Test Case Open',
        description = 'Generate counter testcase and open with Neovim.',
        inputs = {  },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
               .. ' -n '  .. vim.v.servername
        end
    },
    counter_test_case_rule = {
        name = 'Counter Test Case Rule',
        description = 'Generate counter testcase with rules.',
        inputs = { 'main_file_rule', 'correct_file_rule',
                   'generator_file_rule' },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
               .. ' -cr ' .. input.correct_file_rule
               .. ' -gr ' .. input.generator_file_rule
            create_terminal(cmd)
        end
    },
    counter_test_case_rule_open = {
        name = 'Counter Test Case Rule Open',
        description = 'Generate counter testcase with rules and open in '
                   .. 'Neovim.',
        mapping = '<leader>rt',
        inputs = { 'main_file_rule', 'correct_file_rule',
                   'generator_file_rule' },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
               .. ' -cr ' .. input.correct_file_rule
               .. ' -gr ' .. input.generator_file_rule
               .. ' -n '  .. vim.v.servername
            create_terminal(cmd)
        end
    },
    counter_test_case_file = {
        name = 'Counter Test Case File',
        description = 'Generate counter testcase with file names.',
        inputs = { 'correct_file', 'generator_file_rule' },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
               .. ' -cf ' .. current_directory() .. '/' .. input.correct_file
               .. ' -gf ' .. current_directory() .. '/' .. input.generator_file
            create_terminal(cmd)
        end
    },
    counter_test_case_file_open = {
        name = 'Counter Test Case File Open',
        description = 'Generate counter testcase with file names and open '
                   .. 'in Neovim.',
        inputs = { 'correct_file', 'generator_file_rule' },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
               .. ' -cf ' .. current_directory() .. '/' .. input.correct_file
               .. ' -gf ' .. current_directory() .. '/' .. input.generator_file
               .. ' -n '  .. vim.v.servername
            create_terminal(cmd)
        end
    },
    counter_test_case_rule_file = {
        name = 'Counter Test Case Rule File',
        description = 'Generate counter testcase with rules with file '
                   .. 'names.',
        inputs = { 'main_file_rule', 'correct_file', 'correct_file_rule',
                   'generator_file', 'generator_file_rule' },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
               .. ' -cf ' .. current_directory() .. '/' .. input.correct_file
               .. ' -cr ' .. input.correct_file_rule
               .. ' -gf ' .. current_directory() .. '/' .. input.generator_file
               .. ' -gr ' .. input.generator_file_rule
            create_terminal(cmd)
        end
    },
    counter_test_case_rule_file_open = {
        name = 'Counter Test Case Rule File Open',
        description = 'Generate counter testcase with rules with file '
                   .. 'names and open in Neovim.',
        inputs = { 'main_file_rule', 'correct_file', 'correct_file_rule',
                   'generator_file', 'generator_file_rule' },
        command = function(input)
            cmd = script  .. ' countertc'
               .. ' -mf ' .. current_file()
               .. ' -cf ' .. current_directory() .. '/' .. input.correct_file
               .. ' -cr ' .. input.correct_file_rule
               .. ' -gf ' .. current_directory() .. '/' .. input.generator_file
               .. ' -gr ' .. input.generator_file_rule
               .. ' -n '  .. vim.v.servername
            create_terminal(cmd)
        end
    },
}

generate_tasks = {
    generate_file = {
        name = 'Generate File',
        description = 'Generate files.',
        inputs = { 'template', 'new_file' },
        command = function(input)
            cmd = script .. ' genfile'
               .. ' '    .. input.new_file
               .. ' -b ' .. current_directory()
               .. ' -t ' .. input.template
            create_terminal(cmd)
        end
    },
    generate_file_open = {
        name = 'Generate File Open',
        description = 'Generate files and open in Neovim.',
        mapping = '<leader>gf',
        inputs = { 'template', 'new_file' },
        command = function(input)
            cmd = script .. ' genfile'
               .. ' '    .. input.new_file
               .. ' -b ' .. current_directory()
               .. ' -t ' .. input.template
               .. ' -n ' .. vim.v.servername
            create_terminal(cmd)
        end
    },
    generate_file_rule = {
        name = 'Generate File Rule',
        description = 'Generate files with rule.',
        inputs = { 'new_files_rule', 'template', 'new_file' },
        command = function(input)
            cmd = script .. ' genfile'
               .. ' '    .. input.new_file
               .. ' -b ' .. current_directory()
               .. ' -r ' .. input.new_files_rule
               .. ' -t ' .. input.template
            create_terminal(cmd)
        end
    },
    generate_file_rule_open = {
        name = 'Generate File Rule Open',
        description = 'Generate files with rule and open in Neovim.',
        inputs = { 'new_files_rule', 'template', 'new_file' },
        command = function(input)
            cmd = script .. ' genfile'
               .. ' '    .. input.new_file
               .. ' -b ' .. current_directory()
               .. ' -r ' .. input.new_files_rule
               .. ' -t ' .. input.template
               .. ' -n ' .. vim.v.servername
            create_terminal(cmd)
        end
    },
    generate_input = {
        name = 'Generate Input',
        description = 'Generate input files.',
        inputs = { 'io_path' },
        command = function(input)
            cmd = script .. ' geninput'
               .. ' '    .. input.io_path
               .. ' -b ' .. current_directory()
            create_terminal(cmd)
        end
    },
    generate_input_open = {
        name = 'Generate Input Open',
        description = 'Generate input files and open in Neovim.',
        mapping = '<leader>gi',
        inputs = { 'io_path' },
        command = function(input)
            cmd = script .. ' geninput'
               .. ' '    .. input.io_path
               .. ' -b ' .. current_directory()
               .. ' -n ' .. vim.v.servername
            create_terminal(cmd)
        end
    },
    generate_contest = {
        name = 'Generate Contest',
        description = 'Generate contest.',
        inputs = { 'contest_path', 'new_files_rule', 'template', 
                   'task_paths' },
        command = function(input)
            cmd = script .. ' gencontest'
               .. ' '    .. input.task_paths
               .. ' -b ' .. input.contest_path
               .. ' -r ' .. input.new_files_rule
               .. ' -t ' .. input.template
            create_terminal(cmd)
        end
    },
    generate_contest_open = {
        name = 'Generate Contest Open',
        description = 'Generate contest and open in Neovim.',
        mapping = '<leader>gc',
        inputs = { 'contest_path', 'new_files_rule', 'template', 
                   'task_paths' },
        command = function(input)
            cmd = script .. ' gencontest'
               .. ' '    .. input.task_paths
               .. ' -b ' .. input.contest_path
               .. ' -r ' .. input.new_files_rule
               .. ' -t ' .. input.template
               .. ' -n ' .. vim.v.servername
            create_terminal(cmd)
        end
    },
    generate_snippets = {
        name = 'Generate Snippets',
        description = 'Generate snippets.',
        mapping = '<leader>gs',
        inputs = {  },
        command = function(input)
            cmd = script .. ' gensnippets'
            create_terminal(cmd)
        end
    },
    remove_comments = {
        name = 'Remove Comments',
        description = 'Remove comments.',
        mapping = '<leader>gr',
        inputs = { 'io_path' },
        command = function(input)
            cmd = script  .. ' removecomments'
               .. ' -mf ' .. current_file()
            create_terminal(cmd)
        end
    },
    remove_comments_rule = {
        name = 'Remove Comments Rule',
        description = 'Remove comments with a rule.',
        inputs = { 'main_file_rule' },
        command = function(input)
            cmd = script  .. ' removecomments'
               .. ' -mf ' .. current_file()
               .. ' -mr ' .. input.main_file_rule
            create_terminal(cmd)
        end
    },
}

telescope_tasks.extend_categories({
    {
        name = 'Run',
        description = 'Run, check, compile, etc. current file.',
        mapping = '<leader>rr',
        tasks = {
            run_tasks.check,
            run_tasks.input_times,
            run_tasks.counter_test_case_rule_open,
            run_tasks.compile_rule,
            run_tasks.compile,
            run_tasks.input,
            run_tasks.input_rule,
            run_tasks.input_rule_and_times,
            run_tasks.run,
            run_tasks.run_rule,
            run_tasks.check_rule,
            run_tasks.counter_test_case,
            run_tasks.counter_test_case_open,
            run_tasks.counter_test_case_rule,
            run_tasks.counter_test_case_file,
            run_tasks.counter_test_case_file_open,
            run_tasks.counter_test_case_rule_file,
            run_tasks.counter_test_case_rule_file_open,
        }
    },
    {
        name = 'Generate',
        description = 'Generate file, contest, snippets, etc..',
        mapping = '<leader>gg',
        tasks = {
            generate_tasks.generate_input_open,
            generate_tasks.generate_contest_open,
            generate_tasks.remove_comments,
            generate_tasks.generate_snippets,
            generate_tasks.generate_file_open,
            generate_tasks.generate_file,
            generate_tasks.generate_file_rule,
            generate_tasks.generate_file_rule_open,
            generate_tasks.generate_input,
            generate_tasks.generate_contest,
            generate_tasks.remove_comments_rule,
        }
    }
})

