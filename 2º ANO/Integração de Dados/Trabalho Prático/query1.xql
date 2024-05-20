xquery version "1.0";

<html><body>
<h2>Países e Bandeiras</h2>
<ul>
<table>
<tr>
          <th>Nome do País</th>
          <th>Bandeira</th>
</tr>
{
for $x in doc("C:/Users/Utilizador/Documents/NetBeansProjects/TrabalhoPraticoID/paises.xml")//pais
return 
	<tr>
		<td>{data($x/@nome)}</td>
		<td><img src="{$x/bandeira/text()}" height="100px" width="100px"/></img></td>
	</tr>
}
</table>
</ul>
</body></html>