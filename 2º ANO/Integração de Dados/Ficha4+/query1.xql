xquery version "1.0";

for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/escritores.xml")//escritor
where $x/nacionalidade = 'Português' or $x/nacionalidade = 'português'
order by $x/@nome
return ('Nome: ', data($x/@nome), ' -- ', $x/nome_completo/text(), '&#10;')