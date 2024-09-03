using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using PWEB_2324.Data;
using PWEB_2324.Models;
using PWEB_2324.ViewModels;
using System.Collections;

namespace PWEB_2324.Controllers
{
    public class ListImoveisController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<IdentityUser> _userManager;

        public ListImoveisController(ApplicationDbContext context, UserManager<IdentityUser> userManager)
        {
            _context = context;
            _userManager = userManager;
        }
        public async Task<IActionResult> Index(bool? disponivel, string? order)
        {
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.OrderBy(c => c.Nome).ToList(), "Id", "Nome");

            if (disponivel != null)
            {
                if (disponivel == true)
                    ViewData["Title"] = "Lista de Imoveis Activos";
                else
                    ViewData["Title"] = "Lista de Imoveis Inactivos";

                return View(await _context.Imoveis.Include("categoria").
                    Where(c => c.Available == disponivel && c.locador.Ativo==true).OrderBy(c => c.Title).ToListAsync()
                    );
            }
            else if(order != null)
            {
                if(order == "asc")
                {
                    return View(await _context.Imoveis.Include("categoria").Where(c => c.locador.Ativo == true && c.Available == true).OrderBy(c => c.Price).ToListAsync());
                }
                else
                {
                    return View(await _context.Imoveis.Include("categoria").Where(c => c.locador.Ativo == true && c.Available == true).OrderByDescending(c => c.Price).ToListAsync());
                }
            }
            else
            {
                ViewData["Title"] = "Lista de Imoveis";
                return View(await _context.Imoveis.Include("categoria").Where(c => c.locador.Ativo == true && c.Available == true).OrderBy(c => c.Title).ToListAsync());
            }
        }

        [HttpPost]
        public IActionResult Index(string TextoAPesquisar, int CategoriaId, int LocadorId, int TempoMinimo, DateTime DataInicio, DateTime DataFim)
        {
            ViewData["ListaDeCategorias"] = new SelectList(_context.Categorias.OrderBy(c => c.Nome).ToList(), "Id", "Nome");
            ViewData["ListaDeLocadores"] = new SelectList(_context.Locadores.OrderBy(c => c.Nome).ToList(), "Id", "Nome");

            if (string.IsNullOrWhiteSpace(TextoAPesquisar))
            {
                if(CategoriaId != 0 || TempoMinimo != 0)
                {
                    if(DataFim.Date.Year != 1)
                    {
                        var resultado = from c in _context.Imoveis
                                        where c.CategoriaId == CategoriaId && c.LocadorId == LocadorId && c.TempoMin >= TempoMinimo && c.DataInit >= DataInicio && c.DataEnd <= DataFim && c.Available == true && c.locador.Ativo == true
                                        select c;
                        return View(resultado);
                    }
                    else
                    {
                        var resultado = from c in _context.Imoveis
                                        where c.CategoriaId == CategoriaId && c.LocadorId == LocadorId && c.TempoMin >= TempoMinimo && c.DataInit >= DataInicio && c.Available == true && c.locador.Ativo == true
                                        select c;
                        return View(resultado);
                    }
                }
                return View(_context.Imoveis.Where(c => c.CategoriaId == CategoriaId));
            }        
            else
            {
                if(DataFim.Date.Year != 1)
                {
                    var resultado = from c in _context.Imoveis
                                    where c.Localizacao.Contains(TextoAPesquisar) && c.CategoriaId == CategoriaId && c.LocadorId == LocadorId && c.TempoMin >= TempoMinimo && c.DataInit >= DataInicio && c.DataEnd <= DataFim && c.Available == true && c.locador.Ativo == true
                                    select c;
                    return View(resultado);
                }
                else
                {
                    var resultado = from c in _context.Imoveis
                                    where c.Localizacao.Contains(TextoAPesquisar) && c.CategoriaId == CategoriaId && c.LocadorId == LocadorId && c.TempoMin >= TempoMinimo && c.DataInit >= DataInicio && c.Available == true && c.locador.Ativo == true
                                    select c;
                    return View(resultado);
                }

            }
        }

        public async Task<IActionResult> Details(int? id)
        {
            if (id == null || _context.Imoveis == null)
            {
                return NotFound();
            }

            var imo = await _context.Imoveis.Include("categoria")
                .FirstOrDefaultAsync(m => m.Id == id);
            if (imo == null)
            {
                return NotFound();
            }

            return View(imo);
        }
        [Authorize("Client")]
        public async Task<IActionResult> Add(int? id)
        {

            if (id == null || _context.Imoveis == null)
            {
                return NotFound();
            }

            var imo = await _context.Imoveis.FindAsync(id);
            if (imo == null)
            {
                return NotFound();
            }

            return View(imo);
        }

        [Authorize("Client")]
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Add(int id, [Bind("Id,Title,Avaliacao,Descricao,DataInit,DataEnd,TempoMin, ClienteId")] Alugado alug)
        {
            var user = await _userManager.GetUserAsync(User);
            var imo = await _context.Imoveis.FindAsync(id);

            ModelState.Remove(nameof(alug.imovel));
            ModelState.Remove(nameof(alug.cliente));
            ModelState.Remove(nameof(alug.locador));

            if (imo == null)
            {
                return NotFound();
            }
            else
            {
                if((alug.DataInit >= imo.DataInit && alug.DataEnd <= imo.DataEnd) && (alug.TempoMin >= imo.TempoMin))
                {
                    Alugado imovelAlugado = new Alugado(imo.Title, imo.Descricao, user.Id, imo.Id, alug.DataInit, alug.DataEnd, alug.TempoMin, (int)imo.LocadorId);
                    _context.Update(imovelAlugado);
                    await _context.SaveChangesAsync();
                    return RedirectToAction("Index", "ListImoveis");
                }
                else
                {
                    return View();
                }
               
            }
            //return RedirectToAction("Index", "ListImoveis");

            //return View();
        }

        private bool ImovelExists(int id)
        {
            return (_context.Imoveis?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
