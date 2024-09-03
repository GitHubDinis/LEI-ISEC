using System.ComponentModel.DataAnnotations;

namespace PWEB_2324.Models
{
    public class Imovel
    {
        public int Id { get; set; }

        [Display(Name = "Title", Prompt = "Introduza o Título do anuncio!")]
        [Required(ErrorMessage = "Indique o título do anuncio!")]
        public string Title { get; set; }

        [Display(Name = "Descrição", Prompt = "Introduza a Descrição do imovel!")]
        [Required(ErrorMessage = "Descreva o imovel!")]
        public string Descricao { get; set; }

        [Display(Name = "Price", Prompt = "Introduza o preço de arrendamento!")]
        [Required(ErrorMessage = "Indique o preço de arrendamento!")]
        public int Price { get; set; }

        [Display(Name = "Propriedade activo?")]
        public bool Available { get; set; }
        [Display(Name = "Localização", Prompt = "Introduza a Localização do imóvel!")]
        [Required(ErrorMessage = "Indique a localização!")]
        public string Localizacao { get; set; }
        [Display(Name = "Quartos", Prompt = "Introduza o numero de quartos!")]
        [Required(ErrorMessage = "Indique o numero de quartos!")]
        public int Quartos { get; set; }
        [Display(Name = "DataInit", Prompt = "Introduza a data inicial para entrar!")]
        [Required(ErrorMessage = "Indique a data inicial para entrar!")]
        public DateTime DataInit {  get; set; }
        [Display(Name = "DataEnd", Prompt = "Introduza a data de saida!")]
        [Required(ErrorMessage = "Indique a data de saida!")]
        public DateTime DataEnd { get; set; }
        [Display(Name = "TempoMin", Prompt = "Introduza o tempo minimo em meses!")]
        [Required(ErrorMessage = "Indique o tempo minimo em meses!")]
        public int TempoMin {  get; set; }
        [Display(Name = "Avaliacao")]
        public int? Avaliacao { get; set; }
        [Display(Name = "Categoria")]
        public int? CategoriaId { get; set; }
        public Categoria categoria { get; set; }
        public int? LocadorId { get; set; }
        public Locador locador { get; set; }
        public string? ClienteId { get; set; }
        public Cliente cliente { get; set; }
    }

}
