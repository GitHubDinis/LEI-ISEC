xquery version "1.0";

declare variable $v := doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/input.xml")/input/text();

<html><body>
<h2>Ocupações do {$v}</h2>
<ul>
{
for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/escritores.xml")//escritor
where $x/@nome = $v
return 
	for $i in $x//ocupacao
	order by $i
	return <li>{$i/text()}</li>
}
</ul>
</body></html>