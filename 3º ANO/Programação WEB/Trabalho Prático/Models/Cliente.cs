using System.ComponentModel.DataAnnotations;

namespace PWEB_2324.Models
{
    public class Cliente
    {
        public string Id { get; set; }

        [Display(Name = "Cliente", Prompt = "Introduza a nome!")]
        [Required(ErrorMessage = "Indique o nome!")]
        public string Nome { get; set; }

        public ICollection<Imovel> Imoveis { get; set; }
    }
}
