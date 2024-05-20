xquery version "1.0";

<html><body>
<h2>Ocupações do José Saramago</h2>
<ul>
{
for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/escritores.xml")//escritor
where $x/@nome = 'José Saramago'
return 
	for $i in $x//ocupacao
	order by $i
	return <li>{$i/text()}</li>
}
</ul>
</body></html>