using System.ComponentModel.DataAnnotations;

namespace PWEB_2324.Models
{
    public class Categoria
    {
        public int Id { get; set; }

        [Display(Name = "Categoria", Prompt = "Introduza a Categoria!")]
        [Required(ErrorMessage = "Indique o nome da Categoria!")]
        public string Nome { get; set; }

        [Display(Name = "Descrição", Prompt = "Introduza a Descrição da Categoria!")]
        [Required(ErrorMessage = "Descreva a Categoria!")]
        public string Descricao { get; set; }      

        public ICollection<Imovel> Imoveis { get; set; }

    }
}
