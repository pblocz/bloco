import re,sys

from pygments import highlight
from pygments.lexers import PythonLexer
from pygments.formatters import HtmlFormatter

from pygments.lexer import RegexLexer,bygroups,using
from pygments.token import *

from xml.dom.minidom import parse,parseString,Text
from xml.dom import Node

class EbnfLexer(RegexLexer):
    name = 'ebnf'
    aliases = ['ebnf']
    filenames = ['*.ebnf']
    flags=re.MULTILINE | re.DOTALL


    tokens = {
        'root': [
            (r'\(\*',Comment,'comment'),
            (r'\?(?:(?:\\\?)|[^?])*?\?', String.Interpol),#Name.Label),
            (r'\[',Name.Builtin,'bracket'),
            (r'\{',Name.Builtin,'code'),
            (r'".*?"',String),
            (r"'.*?'",String),
            (r"\*|\?|\+",Operator),
            (r"\||=",Keyword),
            (r"\(|\)|,|;",Punctuation),
            (r"[a-zA-Z][a-zA-Z0-9_]*",Name.Variable),
            (r"[ \t\n]+",Generic),
        ],
        'code':[
            (r'(.+?)(\})',bygroups(using(PythonLexer),Name.Builtin),'#pop'),
        ],
        'bracket':[
            (r'[^\]\[]+',Name.Constant),
            (r'\[',Name.Builtin,'#push'),
            (r'\]',Name.Builtin, '#pop'),
        ],
        'comment':[
            (r'[^*]+',Comment),
            (r'\*\)',Comment,'#pop'),
            (r'\*',Comment),
        ]
    }

def innerHTML(root):
    text = u''
    nodes = [ root ]
    while not nodes==[]:
        node = nodes.pop()
        if node.nodeType==Node.TEXT_NODE:
            text += node.wholeText
        else:
            nodes.extend(node.childNodes)
    return text

if __name__=="__main__":

    input=sys.argv[1]
    output=sys.argv[2]

    dom=parse(input)
    pres=dom.getElementsByTagName("pre")
    for pre in pres:
        if "ebnf" not in pre.getAttribute("class"): continue
        v=pre.firstChild.wholeText
        dom1=parseString(highlight(v,EbnfLexer(),HtmlFormatter()))
        pre.removeChild(pre.firstChild)
        pre.appendChild(dom1.documentElement)

        head=dom.getElementsByTagName('head')[0]
        style=dom.createElement("style")
        style.setAttribute("type","text/css")
        txt=Text(); txt.data=HtmlFormatter().get_style_defs('.highlight')

        style.appendChild(txt)
        head.appendChild(style)

        with open(output,"wb") as f:
            f.write(dom.toxml().replace('<title/>','<title></title>')
            .encode('ascii','xmlcharrefreplace'))
# print HtmlFormatter().get_style_defs('.highlight')
# code="[asdf]adsf"
# print highlight(code,EbnfLexer(),HtmlFormatter())
