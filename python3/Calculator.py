import sys

class Token:
	'''
	A class to define a token (because python doesn't have structs)

	params:
		type_ : The type of the token
		value (optional) : The value of the token 
	'''
	def __init__(self, type_, value = None):
		self.type_ = type_
		self.value = value
	def __repr__(self):
		if self.value or self.value == '':
			return f'(Type: {self.type_}, Value = "{self.value}")'
		return f'(Type: {self.type_})'

class Operators:
	plus = '+'
	minus = '-'
	divide = '/'
	multiply = '*'
	negative = '_'
	exponent = '^'
	numbers = '1234567890.'
	paren1 = '('
	paren2 = ')'

	allOps = ' +-/*()^'
	letters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_'

print(Operators.letters.upper())

def Lexer(expression):
	pos = 0
	tokens = []
	num = False
	curNum = ''
	while True:
		if expression[pos] == Operators.plus:
			tokens.append(Token('NUM', curNum))
			tokens.append(Token('PLUS'))
			curNum = ''
			num = False
		elif expression[pos] == Operators.minus:
			tokens.append(Token('NUM', curNum))
			tokens.append(Token('MINUS'))
			curNum = ''
			num = False
		elif expression[pos] == Operators.multiply:
			tokens.append(Token('NUM', curNum))
			tokens.append(Token('MULT'))
			curNum = ''
			num = False
		elif expression[pos] == Operators.divide:
			tokens.append(Token('NUM', curNum))
			tokens.append(Token('DIV'))
			curNum = ''
			num = False
		elif expression[pos] == Operators.exponent:
			tokens.append(Token('NUM', curNum))
			tokens.append(Token('EXP'))
			curNum = ''
			num = False

		elif expression[pos] == Operators.negative:
			curNum += '-'

		elif expression[pos] in Operators.numbers:
			num = True
			curNum += expression[pos]

		elif expression[pos] == Operators.paren2:
			if curNum != '':
				tokens.append(Token('NUM', curNum))
			tokens.append(Token('CGROUP'))
			curNum = ''
			num = False

		elif expression[pos] == Operators.paren1:
			if curNum != '':
				tokens.append(Token('NUM', curNum))
				tokens.append(Token('MULT'))
				num = False
				curNum = ''
			tokens.append(Token('OGROUP'))
			num = False
		'''
		else:
			startPos = pos
			vars = []
			varName = []
			while 0==0:
				if expression[pos] in Operators.all:
					break

				else:
					varName.append(expression[pos])

				try:
					pos += 1
					expression[pos]
				except IndexError:
					break
		'''
		try:
			pos += 1
			expression[pos]
		except IndexError:
			break

	if curNum != '':
		tokens.append(Token('NUM', curNum))

	temp = []
	for tok in tokens:
		if tok.value != '':
			temp.append(tok)
	tokens = temp

	return tokens

def Solve(tokens):
	pos = -1
	while 0==0:
		try:
			pos += 1
			tokens[pos]
		except IndexError:
			break

		if tokens[pos].type_ == 'EXP':
			ans = float(tokens[pos-1].value) ** float(tokens[pos+1].value)
			tokens[pos].value = str(ans)
			tokens[pos].type_ = 'NUM'
			del tokens[pos-1]
			del tokens[pos]

	pos = -1
	while 0==0:
		try:
			pos += 1
			tokens[pos]
		except IndexError:
			break

		if tokens[pos].type_ == 'MULT':
			ans = float(tokens[pos-1].value) * float(tokens[pos+1].value)
			tokens[pos].value = str(ans)
			tokens[pos].type_ = 'NUM'
			del tokens[pos-1]
			del tokens[pos]
			pos = -1
		if tokens[pos].type_ == 'DIV':
			ans = float(tokens[pos-1].value) / float(tokens[pos+1].value)
			tokens[pos].value = str(ans)
			tokens[pos].type_ = 'NUM'
			del tokens[pos-1]
			del tokens[pos]
			pos = -1

	pos = -1
	while 0==0:
		try:
			pos += 1
			tokens[pos]
		except IndexError:
			break

		if tokens[pos].type_ == 'PLUS':
			ans = float(tokens[pos-1].value) + float(tokens[pos+1].value)
			tokens[pos].value = str(ans)
			tokens[pos].type_ = 'NUM'
			del tokens[pos+1]
			del tokens[pos-1]
			pos = -1
		if tokens[pos].type_ == 'MINUS':
			ans = float(tokens[pos-1].value) - float(tokens[pos+1].value)
			tokens[pos].value = str(ans)
			tokens[pos].type_ = 'NUM'
			del tokens[pos+1]
			del tokens[pos-1]
			pos = -1

	return tokens

def Simplify(tokens):
	pos = 0
	isEnded = False
	startPos = 0
	endPos = 0
	while 0==0:
		if tokens[pos].type_ == 'OGROUP':
			startPos = pos+1
			isEnded = False
		if tokens[pos].type_ == 'CGROUP' and not isEnded:
			endPos = pos-1
			isEnded = True
			expList = []
			tokPos = startPos
			while tokPos <= endPos:
				expList.append(tokens[tokPos])
				tokPos += 1
			ans = Solve(expList)
			tokens[startPos - 1] = ans[0]
			tokPos = startPos
			while 0 == 0:
				del tokens[tokPos]
				if tokens[tokPos].type_ == 'CGROUP':
					del tokens[tokPos]
					break
			pos = 0
		try:
			pos += 1
			tokens[pos]
		except IndexError:
			break
	return tokens


print(Lexer(input('>>')))