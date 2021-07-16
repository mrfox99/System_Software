%{
    #include <string>
    #include <vector>
    #include <iostream>

    #include "../inc/Nodes.hpp"

    Statements *ASTRoot;

    extern int yylex();
    extern int yylineno;
    extern char *yytext;

    void yyerror(const char *s) { 
        std::cout << "Syntax error on line: " << yylineno << std::endl;
    }
%}

%union {
    Statements *statements;
    Statement *statement;

    Element *element;
    Label *label;

    Instruction *instruction;
    HALTInstruction *halt_instruction;
    INTInstruction *int_instruction;
    RETInstruction *ret_instruction;
    CALLInstruction *call_instruction;
    JMPInstruction *jmp_instruction;
    JEQInstruction *jeq_instruction;
    JNEInstruction *jne_instruction;
    JGTInstruction *jgt_instruction;
    XCHGInstruction *xchg_instruction;
    ADDInstruction *add_instruction;
    SUBInstruction *sub_instruction;
    MULInstruction *mul_instruction;
    DIVInstruction *div_instruction;
    CMPInstruction *cmp_instruction;
    ANDInstruction *and_instruction;
    ORInstruction *or_instruction;
    XORInstruction *xor_instruction;
    TESTInstruction *test_instruction;
    SHLInstruction *shl_instruction;
    SHRInstruction *shr_instruction;
    IRETInstruction *iret_instruction;

    Directive *directive;
    GlobalDirective *global_directive;
    ExternDirective *extern_directive;
    SectionDirective *section_directive;
    WordDirective *word_directive;
    SkipDirective *skip_directive;
    EquDirective *equ_directive;
    EndDirective *end_directive;

    Operand *operand;
    RegisterOperand *register_operand;
    RegisterIndirectOperand * register_indirect_operand;
    RegisterIndirectLiteralOperand *register_indirect_literal_operand;
    RegisterIndirectSymbolOperand *register_indirect_symbol_operand;
    MemoryLiteralOperand *memory_literal_operand;
    MemorySymbolOperand *memory_symbol_operand;
    ImmediateLiteralOperand *immediate_literal_operand;
    ImmediateSymbolOperand *immediate_symbol_operand;
    SymbolOperand *symbol_operand;
    LiteralOperand *literal_operand;

    OperandArgument *operand_argument;
    RegisterArgument *register_argument;
    LiteralArgument *literal_argument;
    SymbolArgument *symbol_argument;
    
    std::vector<SymbolOperand*> *symbol_operand_vector;
    std::vector<Operand*> *operand_vector;

    std::string *string;
    int token;
    short number;
    char reg;
}

%token <string> IDENTIFIER  
%token <number> NUMBER
%token <reg> REGISTER
%token <token> GLOBAL EXTERN SECTION WORD SKIP EQU END
%token <token> HALT INT IRET
%token <token> CALL RET JMP JEQ JNE JGT
%token <token> PUSH POP XCHG
%token <token> ADD SUB MUL DIV CMP
%token <token> NOT AND OR XOR TEST
%token <token> SHL SHR
%token <token> LDR STR
%token <token> DOLLAR ASTERIX PERCENT PLUS HASH LEFT_BRACKET RIGHT_BRACKET COMMA COLON END_LINE
%token <token> COMMENT

// %type <xchg_instruction> xchg_instruction  literal_operand
%type <statements> statements
%type <statement> statement

%type <element> element
%type <label> label

%type <instruction> instruction
%type <halt_instruction> halt_instruction
%type <int_instruction> int_instruction
%type <ret_instruction> ret_instruction
%type <call_instruction> call_instruction
%type <jmp_instruction> jmp_instruction
%type <jeq_instruction> jeq_instruction
%type <jne_instruction> jne_instruction
%type <jgt_instruction> jgt_instruction
%type <xchg_instruction> xchg_instruction
%type <add_instruction> add_instruction
%type <sub_instruction> sub_instruction
%type <mul_instruction> mul_instruction
%type <div_instruction> div_instruction
%type <cmp_instruction> cmp_instruction
%type <and_instruction> and_instruction
%type <or_instruction> or_instruction
%type <xor_instruction> xor_instruction
%type <test_instruction> test_instruction
%type <shl_instruction> shl_instruction
%type <shr_instruction> shr_instruction
%type <iret_instruction> iret_instruction

%type <directive> directive
%type <global_directive> global_directive
%type <extern_directive> extern_directive 
%type <section_directive> section_directive
%type <word_directive> word_directive
%type <skip_directive> skip_directive 
%type <equ_directive> equ_directive
%type <end_directive> end_directive

%type <operand> operand operand_jump operand_ldr operand_str
%type <register_operand> register_operand
%type <register_indirect_operand> register_indirect_operand
%type <register_indirect_literal_operand> register_indirect_literal_operand
%type <register_indirect_symbol_operand> register_indirect_symbol_operand
%type <memory_literal_operand> memory_literal_operand
%type <memory_symbol_operand> memory_symbol_operand
%type <immediate_literal_operand> immediate_literal_operand
%type <immediate_symbol_operand> immediate_symbol_operand
%type <symbol_operand> symbol_operand
%type <literal_operand> literal_operand 

%type <operand_argument> operand_argument
%type <register_argument> register_argument
%type <literal_argument> literal_argument
%type <symbol_argument> symbol_argument

%type <symbol_operand_vector> symbol_list 
%type <operand_vector> symbol_literal_list

%start program

%%

program:
    statements{
        ASTRoot = $1;
    }
    ;    
statements:
    statement{
        $$ = new Statements();
        if($1 != nullptr)
            $$->addStatement($1);
    }
    | statements statement{
        if($2 != nullptr)
            $1->addStatement($2);
    }
    ;
statement: 
    label END_LINE{
        $$ = new Statement($1);
        yylineno++;
    }
    | label element END_LINE{
        $$ = new Statement($1, $2);
        yylineno++;
    }
    | label COMMENT END_LINE{
        $$ = new Statement($1);
        yylineno++;
    }
    | label element COMMENT END_LINE{
        $$ = new Statement($1, $2);
        yylineno++;
    }
    | element END_LINE{ 
        $$ = new Statement($1);
        yylineno++;
    }
    | COMMENT END_LINE{
        $$ = nullptr;
        yylineno++;
    }
    | element COMMENT END_LINE{
        $$ = new Statement($1);
        yylineno++;
    }
    ;
label:
    IDENTIFIER COLON{
        $$ = new Label(*$1);
        delete $1;   
    }
    ;
element:
    directive{ 
        $$ = $1;
    }
    | instruction{
        $$ = $1;
    }
    ;
directive: 
    GLOBAL symbol_list{
        $$ = new GlobalDirective(*$2);
        delete $2;
    }
    | EXTERN symbol_list{
        $$ = new ExternDirective(*$2);
        delete $2;
    }
    | SECTION IDENTIFIER{ 
        $$ = new SectionDirective(new SymbolOperand(new SymbolArgument(*$2)));
        delete $2;
    }
    | WORD symbol_literal_list{
        $$ = new WordDirective(*$2);
        delete $2;
    }
    | SKIP NUMBER{
        $$ = new SkipDirective(new LiteralOperand(new LiteralArgument($2)));
    }
    | EQU IDENTIFIER COMMA NUMBER{
        $$ = new EquDirective(
                new SymbolOperand(new SymbolArgument(*$2)),
                new LiteralOperand(new LiteralArgument($4))
                );
        delete $2;
    }
    | END {
        $$ = new EndDirective();
    }
    ;
symbol_list:
    IDENTIFIER{
        $$ = new std::vector<SymbolOperand*>();
        $$->push_back(new SymbolOperand(new SymbolArgument(*$1)));
        delete $1;
    }
    | symbol_list COMMA IDENTIFIER{
        $1->push_back(new SymbolOperand(new SymbolArgument(*$3)));
        delete $3;
    }
    ;
symbol_literal_list:
    IDENTIFIER{
        $$ = new std::vector<Operand*>();
        $$->push_back(new SymbolOperand(new SymbolArgument(*$1)));
        delete $1;
    }
    | NUMBER{
        $$ = new std::vector<Operand*>();
        $$->push_back(new LiteralOperand(new LiteralArgument($1)));
    }
    | symbol_literal_list COMMA IDENTIFIER{
        $1->push_back(new SymbolOperand(new SymbolArgument(*$3)));
        delete $3;
    }
    | symbol_literal_list COMMA NUMBER{
        $1->push_back(new LiteralOperand(new LiteralArgument($3)));
    }
    ;
instruction:
    HALT{
        $$ = new HALTInstruction();
    }
    | IRET{
            $$ = new IRETInstruction();
    }
    | RET{
            $$ = new RETInstruction();
    }
    
    | CALL operand_jump{
            $$ = new CALLInstruction($2);
    }
    
    | JMP operand_jump{
            $$ = new JMPInstruction($2);
    }
    | JEQ operand_jump{
            $$ = new JEQInstruction($2);
    }
    | JNE operand_jump{
            $$ = new JNEInstruction($2);
    }
    | JGT operand_jump{
            $$ = new JGTInstruction($2);
    }
    | XCHG REGISTER COMMA REGISTER{ 
        $$ = new XCHGInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | ADD REGISTER COMMA REGISTER{ 
        $$ = new ADDInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | SUB REGISTER COMMA REGISTER{ 
        $$ = new SUBInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | MUL REGISTER COMMA REGISTER{ 
        $$ = new MULInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | DIV REGISTER COMMA REGISTER{ 
        $$ = new DIVInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | CMP REGISTER COMMA REGISTER{ 
        $$ = new CMPInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | AND REGISTER COMMA REGISTER{ 
        $$ = new ANDInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | OR REGISTER COMMA REGISTER{ 
        $$ = new ORInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | XOR REGISTER COMMA REGISTER{ 
        $$ = new XORInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | TEST REGISTER COMMA REGISTER{ 
        $$ = new TESTInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | SHL REGISTER COMMA REGISTER{ 
        $$ = new SHLInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | SHR REGISTER COMMA REGISTER{ 
        $$ = new SHRInstruction(
                new RegisterOperand(new RegisterArgument($2)),
                new RegisterOperand(new RegisterArgument($4))
                );
    }
    | INT REGISTER{
        $$ = new INTInstruction(
            new RegisterOperand(new RegisterArgument($2))
            );
    }
    | PUSH REGISTER{
        $$ = new PUSHInstruction(
            new RegisterOperand(new RegisterArgument($2))
            );
    }
    | POP REGISTER{
        $$ = new POPInstruction(
            new RegisterOperand(new RegisterArgument($2))
            );
    }
    | NOT REGISTER{
        $$ = new NOTInstruction(
            new RegisterOperand(new RegisterArgument($2))
            );
    }
    | LDR REGISTER COMMA operand_ldr{ 
        $$ = new LDRInstruction(
            new RegisterOperand(new RegisterArgument($2)), 
            $4
            );
    }
    | STR REGISTER COMMA operand_str{ 
        $$ = new STRInstruction(
            new RegisterOperand(new RegisterArgument($2)), 
            $4
            );
    }
    ;
operand_jump:
    NUMBER{
        $$ = new ImmediateLiteralOperand(new LiteralArgument($1));
    }
    | IDENTIFIER{
        $$ = new ImmediateSymbolOperand(new SymbolArgument(*$1));
        delete $1;
    }
    | PERCENT IDENTIFIER{
        $$ = new PCSymbolOperand(new SymbolArgument(*$2));
        delete $2;
    }
    | ASTERIX NUMBER{
        $$ = new MemoryLiteralOperand(new LiteralArgument($2));
    }
    | ASTERIX IDENTIFIER{
        $$ = new MemorySymbolOperand(new SymbolArgument(*$2));
        delete $2;
    }
    | ASTERIX REGISTER{
        $$ = new RegisterOperand(
                new RegisterArgument($2)
        );
    }
    | ASTERIX LEFT_BRACKET REGISTER RIGHT_BRACKET{
        $$ = new RegisterIndirectOperand(
                new RegisterArgument($3)
        );
    }
    | ASTERIX LEFT_BRACKET REGISTER PLUS NUMBER RIGHT_BRACKET{
        $$ = new RegisterIndirectLiteralOperand(
                new RegisterArgument($3),
                new LiteralArgument($5)
        );
    }
    | ASTERIX LEFT_BRACKET REGISTER PLUS IDENTIFIER RIGHT_BRACKET{
        $$ = new RegisterIndirectSymbolOperand(
                new RegisterArgument($3),
                new SymbolArgument(*$5)
        );
    }
    ;
operand_ldr:
    DOLLAR NUMBER{
        $$ = new ImmediateLiteralOperand(new LiteralArgument($2));
    }
    | DOLLAR IDENTIFIER{
        $$ = new ImmediateSymbolOperand(new SymbolArgument(*$2));
        delete $2;
    }
    | NUMBER{
        $$ = new MemoryLiteralOperand(new LiteralArgument($1));
    }
    | IDENTIFIER{
        $$ = new MemorySymbolOperand(new SymbolArgument(*$1));
        delete $1;
    }
    | PERCENT IDENTIFIER{
        $$ = new PCSymbolOperand(new SymbolArgument(*$2));
        delete $2;
    }
    | REGISTER{
        $$ = new RegisterOperand(new RegisterArgument($1));
    }
    | LEFT_BRACKET REGISTER RIGHT_BRACKET{
        $$ = new RegisterIndirectOperand(new RegisterArgument($2));
    }
    | LEFT_BRACKET REGISTER PLUS NUMBER RIGHT_BRACKET{
        $$ = new RegisterIndirectLiteralOperand(
            new RegisterArgument($2),
            new LiteralArgument($4)
            );
    }
    | LEFT_BRACKET REGISTER PLUS IDENTIFIER RIGHT_BRACKET{
        $$ = new RegisterIndirectSymbolOperand(
            new RegisterArgument($2),
            new SymbolArgument(*$4)
            );
            delete $4;
    }
    ;
operand_str:
    NUMBER{
        $$ = new MemoryLiteralOperand(new LiteralArgument($1));
    }
    | IDENTIFIER{
        $$ = new MemorySymbolOperand(new SymbolArgument(*$1));
        delete $1;
    }
    | PERCENT IDENTIFIER{
        $$ = new PCSymbolOperand(new SymbolArgument(*$2));
        delete $2;
    }
    | REGISTER{
        $$ = new RegisterOperand(new RegisterArgument($1));
    }
    | LEFT_BRACKET REGISTER RIGHT_BRACKET{
        $$ = new RegisterIndirectOperand(new RegisterArgument($2));
    }
    | LEFT_BRACKET REGISTER PLUS NUMBER RIGHT_BRACKET{
        $$ = new RegisterIndirectLiteralOperand(
            new RegisterArgument($2),
            new LiteralArgument($4)
            );
    }
    | LEFT_BRACKET REGISTER PLUS IDENTIFIER RIGHT_BRACKET{
        $$ = new RegisterIndirectSymbolOperand(
            new RegisterArgument($2),
            new SymbolArgument(*$4)
            );
            delete $4;
    }
    ;
%%