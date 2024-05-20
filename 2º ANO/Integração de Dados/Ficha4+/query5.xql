xquery version "1.0";

<html><body>
<h2>Escritores</h2>
<ul>
<table>
{
for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/Ficha4/escritores.xml")//escritor
return 
	<tr>
		<td>$x/foto/text()</td>
		<td>$x/@nome</td>
		<td>$x/nacionalidade/text()</td>
	</tr>
}
</table>
</ul>
</body></html>